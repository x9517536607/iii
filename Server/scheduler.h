#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QObject>
#include <QDebug>
#include <qtimer.h>
#include <QNetworkRequest>
#include <QNetworkReply>

class scheduler : public QObject
{
    Q_OBJECT
public:
    explicit scheduler(QObject *parent = 0);

signals:

public slots:
    void readEventFromServer();
    void onfinish(QNetworkReply *rep);
private:
    double GetDistance(double Lat1, double Long1, double Lat2, double Long2);
};

#endif // SCHEDULER_H
