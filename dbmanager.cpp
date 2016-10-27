#include <dbmanager.h>
#include <QSqlQuery>
//#include <QSqlError>
#include <QSqlRecord>
#include <iostream>
#include <QVariant>
#include <QDebug>

DbManager::DbManager(const QString &path)
{
    someDatabase = QSqlDatabase::addDatabase("QSQLITE");
    someDatabase.setDatabaseName(path);

    if (!someDatabase.open()) {
        qDebug() << "Error; connection failed";
    }
    else {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (someDatabase.isOpen()) {
        someDatabase.close();
    }
}

void DbManager::printTables() const
{
    qDebug() << "Tables:\n";
    //Sqlsqlite_master - all tables from the file
    QSqlQuery query("SELECT name FROM sqlite_master WHERE type='table'");
    //int idName = query.record().indexOf("name");
    while (query.next()) {
        qDebug().noquote() << query.value(0).toString();
    }
}

bool DbManager::isOpen() const
{
    return someDatabase.isOpen();
}
