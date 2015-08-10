#include "mysql.h"

mySQL *mySQL::m_mySQL = 0;

mySQL::mySQL()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("busLocation");
    db.setUserName("root");
    db.setPassword("root");
}

mySQL *mySQL::getInstance()
{
    if(!m_mySQL)
        m_mySQL = new mySQL();
    return m_mySQL;
}

bool mySQL::isConnect()
{
    return db.open();
}
