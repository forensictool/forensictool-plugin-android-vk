#include <dbmanager.h>
#include <QSqlQuery>
#include <QSqlRecord>
#include <iostream>
#include <QVariant>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QSqlField>
#include <QDir>


DbManager::DbManager(const QString &path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open()) {
        qDebug() << "Error; connection failed";
    }
    else {
        qDebug() << "Database: connection ok";
    }
}


DbManager::~DbManager()
{
    if (db.isOpen()) {
        db.close();
    }
}


void DbManager::printTables() const
{
    QStringList tables = db.tables(QSql::Tables);
    int i;
    for (i=0; i<tables.length(); i++) {
        qDebug() << tables[i];
    }
}


bool DbManager::isOpen() const
{
    return db.isOpen();
}


void DbManager::toXML()
{
    int i,j,k;
    QStringList tables = db.tables(QSql::Tables);
    QSqlRecord record;
    QSqlQuery query;
    int numOfFields;
    QXmlStreamWriter xmlWriter;    
    QDir::setCurrent("/home/alexey/QtProjects/databaseproject0/");
    QFile file ("output.xml");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error opening file";
    }
    else {
        xmlWriter.setDevice(&file);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("tables");
        for (i=0; i<tables.length(); i++) {
            xmlWriter.writeStartElement(tables[i]);
            query.exec("SELECT * FROM " + tables[i]);
            while (query.next()) {
            //for (j=0; j<numOfRows; j++) {
                xmlWriter.writeStartElement("record");
                record = db.record(tables[i]);
                numOfFields = record.count();
                for (k=0; k<numOfFields; k++) {
                    if (QString(query.value(k).typeName()) == "QByteArray") {
                        //**********************************BLOB НЕ ПИШЕТСЯ*********************
                    }
                    else {
                        xmlWriter.writeAttribute(record.fieldName(k), query.value(k).toString());
                    }
                }
                xmlWriter.writeEndElement();
            }
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
}
