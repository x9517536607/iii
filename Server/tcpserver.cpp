#include "tcpserver.h"
#include "sockethandler.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include "constantString.h"

tcpServer::tcpServer(QObject *parent) :
    QTcpServer(parent)
{
}

void tcpServer::startServer()
{
    int port = CAMERATCPPORT;

    if(!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Could not start TCP server";
    }
    else
    {
        qDebug() << "TCP listening to port " << port << "...";
    }
}

void tcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting...";
    // setting timeout
    int enableKeepAlive = 1;
    setsockopt(socketDescriptor, SOL_SOCKET, SO_KEEPALIVE, &enableKeepAlive, sizeof(enableKeepAlive));
    int maxIdle = 10; /*10 seconds */
    setsockopt(socketDescriptor, IPPROTO_TCP, TCP_KEEPIDLE, &maxIdle, sizeof(maxIdle));
    int count = 3;  // send up to 3 keepalive packets out, then disconnect if no response
    setsockopt(socketDescriptor, SOL_TCP, TCP_KEEPCNT, &count, sizeof(count));
    int interval = 2;   // send a keepalive packet out every 2 seconds (after the 5 second idle period)
    setsockopt(socketDescriptor, SOL_TCP, TCP_KEEPINTVL, &interval, sizeof(interval));
    //
    socketHandler *thread = new socketHandler(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
