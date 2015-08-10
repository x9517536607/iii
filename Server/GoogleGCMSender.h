#ifndef GOOGLEGCMSENDER_H
#define GOOGLEGCMSENDER_H

#include <QObject>
#include <QThread>
#include <QNetworkRequest>
#include <QNetworkReply>

class GoogleGCMSender : public QObject
{
public:
    static GoogleGCMSender *getInstance();
    void sendMessages(QString regId, QString message);
private:
    GoogleGCMSender();
    static GoogleGCMSender *m_GoogleGCMSender;

signals:

public slots:

};


class MessageSender : public QThread
{
    Q_OBJECT
public:
    explicit MessageSender(QString regId, QString message, QObject *parent);
    virtual void run();

signals:


public slots:
    void onfinish(QNetworkReply *rep);

private:
   QString regId;
   QString message;
};
#endif // GOOGLEGCMSENDER_H
