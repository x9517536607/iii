#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class tcpServer : public QTcpServer
{
public:
    Q_OBJECT
   public:
       explicit tcpServer(QObject *parent = 0);
       void startServer();
   signals:

   public slots:

   protected:
       void incomingConnection(qintptr socketDescriptor);
};

#endif // TCPSERVER_H
