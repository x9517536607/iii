#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>

class udpServer : public QObject
{
    Q_OBJECT
public:
    explicit udpServer(QObject *parent = 0);
    ~udpServer();
signals:
private:
    QUdpSocket *socket;
public slots:
    void readyRead();

};

#endif // UDPSERVER_H
