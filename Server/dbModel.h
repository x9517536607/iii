#ifndef DBMODEL_H
#define DBMODEL_H
#include <QtSql/QSqlQuery>
#include <QDebug>
#endif // DBMODEL_H
class dbModel
{
    public:
        static void insertBus(QString busName, QString busIp, QString latitude, QString longitude, QString regId)
        {
            QString sql = QString("INSERT INTO busLocation (busName,busIp,latitude,longitude,regId,updateTime)VALUES (\"%1\",\"%2\",%3,%4,\"%5\",NOW()) ON DUPLICATE KEY UPDATE busIp=VALUES(busIp),latitude=VALUES(latitude),longitude=VALUES(longitude),regId=VALUES(regId),updateTime=VALUES(updateTime)")
                    .arg(busName, busIp, latitude, longitude, regId);
            QSqlQuery query;
            //qDebug()<<sql;
            query.exec(sql);
        }

        static void insertCamera(QString cameraName, QString cameraIp, QString latitude, QString longitude, bool isOnline)
        {
            QString sql = QString("INSERT INTO cameraLocation (cameraName,cameraIp,latitude,longitude,isOnline)VALUES (\"%1\",\"%2\",%3,%4,%5) ON DUPLICATE KEY UPDATE cameraIp=VALUES(cameraIp),latitude=VALUES(latitude),longitude=VALUES(longitude),isOnline=VALUES(isOnline)")
                    .arg(cameraName, cameraIp, latitude, longitude, isOnline?"1":"0");
            //qDebug()<<sql;
            QSqlQuery query;
            query.exec(sql);
        }

        static QSqlQuery allOnlineBus()
        {
            QString sql = QString("SELECT * FROM busLocation WHERE regId <> \"\" AND TIME_TO_SEC(TIMEDIFF(NOW(),updateTime)) < 300");
            //qDebug()<<sql;
            QSqlQuery query;
            query.exec(sql);
            return query;
        }

        static QSqlQuery allOnlineCamera()
        {
            QString sql = QString("SELECT * FROM cameraLocation WHERE isOnline = 1");
            //qDebug()<<sql;
            QSqlQuery query;
            query.exec(sql);
            return query;
        }
};
