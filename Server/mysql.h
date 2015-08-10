#ifndef MYSQL_H
#define MYSQL_H
#include "QObject"
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>

class mySQL : public QObject
{
public:
    static mySQL *getInstance();
    static bool isConnect();
private:
    mySQL();
    static mySQL *m_mySQL;
    QSqlDatabase db;
};

#endif // MYSQL_H
