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


//get a vector of tables
QVector<QString> DbManager::getTables() const
{
    //tables vector
    QVector<QString> tablesVector;
    //get tables vector
    QSqlQuery query ("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name");
    while (query.next()) {
        tablesVector.push_back(query.value(0).toString());
    }
    return tablesVector;
}


//get a vector of table fields
QVector<QString> DbManager::getTableFeilds(const QString &tableName) const
{
    int j;
    QString sql; //SQL code used for creating a table
    QSqlQuery querySqlFromSqlMaster; //query to get the SQL code//get a vector of tables
    QVector<QString> fieldsVector; //field names vector
    QString fieldName, firstIndex, lastIndex; //first and last indexes of field name
        querySqlFromSqlMaster.exec("SELECT sql FROM sqlite_master WHERE name='" + tableName + "'");
        while(querySqlFromSqlMaster.next()) {
            fieldName = "";
            sql = querySqlFromSqlMaster.value(0).toString();
            firstIndex = sql.indexOf("(")+1;
            lastIndex = sql.indexOf(" ", firstIndex);
            //getting the field names from the sql variable
            //*****************************ДОДЕЛАТЬ ЗДЕСЬ. БЕРЕТСЯ ТОЛЬКО ПЕРВОЕ ПОЛЕ**************************************
            for (j=firstIndex; j<lastIndex; j++){
                fieldName.append(sql[j]);
            }
            fieldsVector.push_back(fieldName);
            qDebug() << sql;
            qDebug() << fieldName;
        }
     return fieldsVector;
}


void DbManager::printTables() const
{
    qDebug() << "Tables:\n";
    QSqlQuery queryTablesFromSqlmaster ("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name");
    while (queryTablesFromSqlmaster.next()) {
        qDebug().noquote() << queryTablesFromSqlmaster.value(0).toString();
    }

    //**********************************test************************************
    QVector<QString> tablesVector = DbManager::getTables();
    qDebug().noquote() << tablesVector;
    const QString messages = "messages";
    QVector<QString> fieldsVector = DbManager::getTableFeilds(messages);
    qDebug().noquote() << fieldsVector;

    /*int i,j;
    QString sql = "atat";
    QSqlQuery querySqlFromSqlMaster;
    QVector<QString> fields;
    for (i=0; i<tablesVector.length(); i++) {
        querySqlFromSqlMaster.exec("SELECT sql FROM sqlite_master WHERE name='" + tablesVector[i] + "'");
        while(querySqlFromSqlMaster.next()) {
            sql = querySqlFromSqlMaster.value(0).toString();
            qDebug() << sql;
        }
        /*for (j=sql.indexOf("(")+1; sql[j]!=' '; j++) {
            tablesVector[i].append(sql[j]);
        }*/
    //}*/
    //qDebug() << sql;
   // qDebug() << tables;

    /*QVector<QString> test;
    test.append("dad");
    qDebug() << test[0];*/


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
        /*while(queryFields.next()) {
            sql = queryFields.value(0).toString();
           // qDebug().noquote() << sql;
        }*/
    //select sql from sqlite_master where name = 'messages'
    //CREATE TABLE `messages` (mid int unique, peer int not null, sender int not null, text text, time int not null, attachments blob, fwd blob, extras text, flags int not null, random_id int)

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
}
