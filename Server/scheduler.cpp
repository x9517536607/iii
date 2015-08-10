#include "scheduler.h"
#include "math.h"
#include <QtXml/QDomDocument>
#include "GoogleGCMSender.h"
#include "dbModel.h"
#include <QSqlQuery>
#include <QList>

scheduler::scheduler(QObject *parent) :
    QObject(parent)
{
    QTimer *readEventFromServerTimer;
    readEventFromServerTimer = new QTimer(this);
    readEventFromServerTimer->start(10000);
    QObject::connect(readEventFromServerTimer,SIGNAL(timeout()),this,SLOT(readEventFromServer()));
}

void scheduler::readEventFromServer()
{
    QNetworkAccessManager * mgr = new QNetworkAccessManager(this);
    connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(onfinish(QNetworkReply*)));
    connect(mgr,SIGNAL(finished(QNetworkReply*)),mgr,SLOT(deleteLater()));
    QByteArray postData;
    postData.append("Comm=GetXML");
    QNetworkRequest request = QNetworkRequest(QUrl("http://219.87.82.201:8080/examples/servlets/servlet/SessionExample"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    mgr->post(request, postData);
}

void scheduler::onfinish(QNetworkReply *rep)
{
    QDomDocument document;
    if(!document.setContent(QString(rep->readAll())))
    {
        qDebug() << "file not read!";
        return;
    }

    if(document.isNull())
    {
        qDebug() << "file not read!";
        return;
    }
    QDomElement root = document.documentElement();
    QDomNodeList roadData = root.elementsByTagName("Road_data");
    QDomNode n = roadData.at(0).firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            QString time = e.elementsByTagName("keytime").at(0).toElement().text();
            QString region = e.elementsByTagName("region").at(0).toElement().text();
            QString road1 = e.elementsByTagName("road1").at(0).toElement().text();
            double X1 = e.elementsByTagName("GPS").at(0).toElement().elementsByTagName("X1").at(0).toElement().text().toDouble();
            double Y1 = e.elementsByTagName("GPS").at(0).toElement().elementsByTagName("Y1").at(0).toElement().text().toDouble();
            double X2 = e.elementsByTagName("GPS").at(0).toElement().elementsByTagName("X2").at(0).toElement().text().toDouble();
            double Y2 = e.elementsByTagName("GPS").at(0).toElement().elementsByTagName("Y2").at(0).toElement().text().toDouble();
            QString GPS = QString("<%1,%2><%3,%4>").arg(QString::number(X1), QString::number(Y1), QString::number(X2), QString::number(Y2));
            QString roadtype = e.elementsByTagName("roadtype").at(0).toElement().text();
            QString comment = e.elementsByTagName("Comment").at(0).toElement().text();
            QString result = QString("時間: %1\n地點: %2 - %3 (%4)\n事件: %5 - %6")
            .arg(time, region, road1, GPS, roadtype, comment);
            //qDebug() << result;
            QSqlQuery allCamera = dbModel::allOnlineCamera();
            QString cameraInRange = "";
            while(allCamera.next())
            {
                double distance = GetDistance(Y1, X1, allCamera.value(3).toDouble(), allCamera.value(4).toDouble());
                if(distance < 0.5)
                {
                    cameraInRange.push_back(QString("%1,").arg(allCamera.value(1).toString()));
                }
            }
            if(cameraInRange.indexOf(",") > -1)
            {
                QSqlQuery allBus = dbModel::allOnlineBus();
                while(allBus.next())
                {
                    double distance = GetDistance(Y1, X1, allBus.value(3).toDouble(), allBus.value(4).toDouble());
                    //GoogleGCMSender::getInstance()->sendMessages(allBus.value(5).toString(), result);
                    if(distance > 0.5 && distance < 3)
                    {
                        cameraInRange = cameraInRange.left(cameraInRange.length() - 1);
                        GoogleGCMSender::getInstance()->sendMessages(allBus.value(5).toString(), QString("%1\n%2").arg(result, cameraInRange));
                    }
                }
            }

        }
        n = n.nextSibling();
    }
}

double scheduler::GetDistance(double Lat1, double Long1, double Lat2, double Long2)
{
    double Lat1r = (M_PI/180)*Lat1;
    double Lat2r = (M_PI/180)*Lat2;
    double Long1r = (M_PI/180)*Long1;
    double Long2r = (M_PI/180)*Long2;

    double R = 6371; // Earths radius (km)
    double d = acos(sin(Lat1r) *
    sin(Lat2r) + cos(Lat1r) *
    cos(Lat2r) *
    cos(Long2r-Long1r)) * R;
    return d;
}

//時間: <keytime>
//地點: <region> - <road1> (<GPS>)
//事件: <roadtype> - <comment>
