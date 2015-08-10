#include "udpserver.h"
#include "dbModel.h"
#include "constantString.h"

udpServer::udpServer(QObject *parent) :
    QObject(parent)
{
    socket = new QUdpSocket(this);
    int port = BUSUDPPORT;
    if(!socket->bind(QHostAddress::Any, port))
    {
        qDebug() << "Could not start UDP server";
    }
    else
    {
        qDebug() << "UDP listening to port " << port << "...";
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

udpServer::~udpServer()
{
    socket->close();
}

void udpServer::readyRead()
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
    QStringList data = QString(buffer).split(",");
    qDebug()<<data.length();
    if(data.length() == 4)
        dbModel::insertBus(data[0], sender.toString(), data[2], data[1], data[3]);
    qDebug() << "UDP Message from: " << sender.toString();
    qDebug() << "UDP Message: " << buffer;
}
