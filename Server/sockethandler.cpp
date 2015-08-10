#include "sockethandler.h"
#include <qhostaddress.h>
#include "servicesingleton.h"
#include "dbModel.h"


socketHandler::socketHandler(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
    this->streamName = "";
    this->sms1 = NULL;
    this->sms2 = NULL;
}

void socketHandler::run()
{
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    clientIP = socket -> peerAddress().toString();
    qDebug() << socketDescriptor << " Client connected";
    qDebug() << socket -> peerAddress().toString();

    exec();
}

void socketHandler::readyRead()
{
    QByteArray Data = socket->readAll();
    qDebug() << socketDescriptor << " TCP data in: " << Data;
    QStringList data = QString(Data).split(",");
    if(data.length() == 3)
    {
        if(streamName == "")
        {
            streamName = data[0];
            sms2 = serviceSingleton::getInstance()->createMediaSession(QString("rtsp://%1:554/live2.sdp").arg(clientIP).toStdString().c_str(), (streamName + "2").toStdString().c_str());
            serviceSingleton::getInstance()->addMediaSesstion(sms2);
            sms1 = serviceSingleton::getInstance()->createMediaSession(QString("rtsp://%1:554/live.sdp").arg(clientIP).toStdString().c_str(), (streamName + "1").toStdString().c_str());
            serviceSingleton::getInstance()->addMediaSesstion(sms1);
            dbModel::insertCamera(data[0], socket -> peerAddress().toString(), data[2], data[1], true);
        }
    }
    socket->write(Data);
}

void socketHandler::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    if(sms1 != NULL && sms2 != NULL)
    {
        serviceSingleton::getInstance()->removeMediaSession(sms2);
        serviceSingleton::getInstance()->removeMediaSession(sms1);
        dbModel::insertCamera(streamName, socket -> peerAddress().toString(), "0", "0", false);
    }
    socket->deleteLater();
    exit(0);
}
