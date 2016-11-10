#include <dbmanager.h>
#include <QSqlQuery>
//#include <QSqlError>
#include <QSqlRecord>
#include <iostream>
#include <QVariant>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>


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
    //qDebug() << "Tables:\n";
    //Sqlsqlite_master - all tables from the file
   /* QSqlQuery query ("SELECT sender, text FROM messages ORDER BY sender");
    while (query.next()) {
        qDebug().noquote() << query.value(0).toString();
        qDebug().noquote() << query.value(1).toString();*/
    QSqlQuery query ("SELECT name FROM sqlite_master WHERE type='table'");
    while (query.next()) {
        qDebug().noquote() << query.value(0).toString();
    }
}


bool DbManager::isOpen() const
{
    return someDatabase.isOpen();
}


//void DbManager::toXML(const QString &path)
void DbManager::toXML()
{
    QXmlStreamWriter xmlWriter;
    QFile file ("output.xml");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error opening file";
        }
    else {
        QSqlQuery queryTables ("SELECT name FROM sqlite_master WHERE type='table'");
        xmlWriter.setDevice(&file);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("tables");
        while (query.next()) {
            xmlWriter.writeStartElement(queryTables.value(0).toString());
            xmlWriter.writeEndElement();
        }

        QSqlQuery query ("");
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
}
