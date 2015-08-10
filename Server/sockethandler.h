#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <QThread>
#include <QtNetwork/qtcpsocket.h>
#include <QDebug>
#include "ServerMediaSession.hh"

class socketHandler : public QThread
{
    Q_OBJECT
public:
    explicit socketHandler(qintptr ID, QObject *parent = 0);
    void run();

signals:
    void error(QTcpSocket::SocketError sockererror);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    ServerMediaSession *sms1;
    ServerMediaSession *sms2;
    QString streamName;
    QString clientIP;
};

#endif // SOCKETHANDLER_H
