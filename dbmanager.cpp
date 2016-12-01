#include <dbmanager.h>
#include <QSqlQuery>
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


//get a vector of table fields from SQL query for creating a table
//не работает корректно (см. imported_contacts перед последней скобкой)
//посмотреть синтаксис create table
QVector<QString> DbManager::getTableFeilds(const QString &tableName) const
{
    int j=0;
    int firstIndex, lastIndex; //first and last indexes of a field name
    QString sql; //SQL code used for creating a table
    QSqlQuery querySqlFromSqlMaster; //query to get the SQL code
    QVector<QString> fieldsVector; //field names vector
    QString fieldName;
        //getting the SQL code for the table
        querySqlFromSqlMaster.exec("SELECT sql FROM sqlite_master WHERE name='" + tableName + "'");
        while(querySqlFromSqlMaster.next()) {
            fieldName = "";            
            sql = querySqlFromSqlMaster.value(0).toString(); //string containing sql code
            //firstIndex of the field name, lastIndex - last index of the field name
            firstIndex = sql.indexOf("(")+1;
            lastIndex = sql.indexOf(" ", firstIndex);
            //getting the field names from the sql variable
            //indexOf returns -1 if substring is not found (firstIndex = 1 when not found because of +2 later)
            while (firstIndex != 1) {
                for (j=firstIndex; j<lastIndex; j++){
                    fieldName.append(sql[j]);
                }
                firstIndex = sql.indexOf(",", lastIndex)+2;
                lastIndex = sql.indexOf(" ", firstIndex);
                fieldsVector.push_back(fieldName);
                fieldName = "";
            }
        }
     return fieldsVector;
}


void DbManager::printTables() const
{
    qDebug() << "Tables:\n";

    //**********************************test************************************
    QVector<QString> tablesVector = DbManager::getTables();
    qDebug().noquote() << tablesVector;

    const QString messages = "messages";
    QVector<QString> fieldsVector = DbManager::getTableFeilds(messages);
    //qDebug().noquote() << fieldsVector;

    int i;
    for (i=0; i<tablesVector.length(); i++) {
       fieldsVector = DbManager::getTableFeilds(tablesVector[i]);
       qDebug().noquote() << fieldsVector;
    }

    //***********************************PRINT SQL QUERY FOR EACH TABLE********************************************
    int j;
    QString sql = "atat";
    QSqlQuery querySqlFromSqlMaster;
    QVector<QString> fields;
    for (i=0; i<tablesVector.length(); i++) {
        querySqlFromSqlMaster.exec("SELECT sql FROM sqlite_master WHERE name='" + tablesVector[i] + "'");
        while(querySqlFromSqlMaster.next()) {
            sql = querySqlFromSqlMaster.value(0).toString();
            qDebug() << sql;
        }
        for (j=sql.indexOf("(")+1; sql[j]!=' '; j++) {
            tablesVector[i].append(sql[j]);
        }
    }
}


bool DbManager::isOpen() const
{
    return someDatabase.isOpen();
}


//void DbManager::toXML(const QString &path)
void DbManager::toXML()
{
    int i=0,j=0;
    QXmlStreamWriter xmlWriter;
    //field names
    QVector<QString> fieldsVector;
    //table names
    QVector <QString> tablesVector = DbManager::getTables();
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
            //fields.push_back(queryTables.value(0).toString());
            xmlWriter.writeStartElement(queryTables.value(0).toString());
            xmlWriter.writeStartElement("record");
            fieldsVector = DbManager::getTableFeilds(tablesVector[i]);
            for (j=0; j<fieldsVector.length(); j++) {
                xmlWriter.writeAttribute(fieldsVector[j], "0,"); //VALUE POMENYATb
            }
            xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
            i++;
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
}
