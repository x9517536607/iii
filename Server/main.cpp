#include "mainwindow.h"
#include <QApplication>
#include "tcpserver.h"
#include "udpserver.h"
#include "scheduler.h"
#include "constantString.h"
#include <QtSql>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //DB connect
    QSqlDatabase db = QSqlDatabase::addDatabase(DATABASE);
    db.setHostName(DATABASEHOSTNAME);
    db.setDatabaseName(DATABASENAME);
    db.setUserName(DATABASEUSER);
    db.setPassword(DATABASEPASS);
    if(!db.open()) qDebug() << "DB cannot access!!!";
    //end DB connect
    //start service
    scheduler myscheduler;
    tcpServer myTcpServer;
    myTcpServer.startServer();
    udpServer myUdpServer;
    //end start service
    MainWindow *window = new MainWindow();
    window->show();
    return a.exec();
}
