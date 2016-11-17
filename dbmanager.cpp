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
    qDebug() << "Tables:\n";

    //tables vector
    QVector<QString> tables;
    //get tables vector
    QSqlQuery query ("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name");
    while (query.next()) {
        tables.push_back(query.value(0).toString());
        qDebug().noquote() << query.value(0).toString();
        qDebug().noquote() << tables;
    }
    int i,j;
    QString sql;
    QSqlQuery queryFields;
    QVector<QString> fields;
    for (i=0; i<=tables.length(); i++) {
        queryFields.exec("SELECT sql FROM sqlite_master WHERE name='" + tables[i] + "'");
        while(queryFields.next()) {
            sql = queryFields.value(0).toString();
        }
        for (j=sql.indexOf("(")+1; sql[j]!=' '; j++) {
            tables[i].append(sql[j]);
        }
    }
    qDebug() << sql;
   // qDebug() << tables;

    QVector<QString> test;
    test.append("dad");
    qDebug() << test[0];


    //select sql from sqlite_master where name = 'messages'
    //CREATE TABLE `messages` (mid int unique, peer int not null, sender int not null, text text, time int not null, attachments blob, fwd blob, extras text, flags int not null, random_id int)
    //QSqlQuery query ("SELECT sql FROM sqlite_master WHERE name = '' table_info(table_name)");

}


bool DbManager::isOpen() const
{
    return someDatabase.isOpen();
}


//void DbManager::toXML(const QString &path)
void DbManager::toXML()
{
    QXmlStreamWriter xmlWriter;
    //field names
    QVector<QString> fields;
    QFile file ("output.xml");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error opening file";
        }
    else {
        QSqlQuery queryTables ("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name");
        xmlWriter.setDevice(&file);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("tables");
        while (queryTables.next()) {
            fields.push_back(queryTables.value(0).toString());
            xmlWriter.writeStartElement(queryTables.value(0).toString());
            xmlWriter.writeEndElement();
        }
        QSqlQuery queryFields("SELECT sql FROM sqlite_master WHERE name='" + fields[0] + "'");
        QString sql;
        while(queryFields.next()) {
            sql = queryFields.value(0).toString();
        }
    //select sql from sqlite_master where name = 'messages'
    //CREATE TABLE `messages` (mid int unique, peer int not null, sender int not null, text text, time int not null, attachments blob, fwd blob, extras text, flags int not null, random_id int)

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
}
