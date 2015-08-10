#include "GoogleGCMSender.h"
#include "qdebug.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "constantString.h"

GoogleGCMSender *GoogleGCMSender::m_GoogleGCMSender = 0;

GoogleGCMSender::GoogleGCMSender()
{
}

GoogleGCMSender *GoogleGCMSender::getInstance()
{
    if(!m_GoogleGCMSender)
        m_GoogleGCMSender = new GoogleGCMSender();
    return m_GoogleGCMSender;
}

void GoogleGCMSender::sendMessages(QString regId, QString message)
{
    MessageSender *sender = new MessageSender(regId,message,this);
    sender->run();
}

//Message sneder thread

MessageSender::MessageSender(QString regId, QString message, QObject *parent = 0):
    QThread(parent)
{
    this->regId = regId;
    this->message = message;
}

void MessageSender::run()
{
    QJsonObject GCMJson;
    QJsonArray regIds;
    regIds.insert(0, regId);
    GCMJson.insert("registration_ids",regIds);
    QJsonObject JsonMessage;
    JsonMessage.insert("message", message);
    GCMJson.insert("data",JsonMessage);

    QJsonDocument document;
    document.setObject(GCMJson);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);
    qDebug() << json_str;

    QNetworkAccessManager * mgr = new QNetworkAccessManager(this);
    connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(onfinish(QNetworkReply*)));
    connect(mgr,SIGNAL(finished(QNetworkReply*)),mgr,SLOT(deleteLater()));
    QNetworkRequest request(QUrl("https://android.googleapis.com/gcm/send"));
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Authorization", QString("key=%1").arg(GOOGLEAPIKEY).toStdString().c_str());
    mgr->post(request, byte_array);

}

void MessageSender::onfinish(QNetworkReply *rep)
{
    qDebug() << QString(rep->readAll());
}
