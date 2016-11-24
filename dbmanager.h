#ifndef DBMANAGER
#define DBMANAGER

#include <QSqlDatabase>
#include <QVector>

class DbManager
{
public:
    //constructor; path - path to db
    DbManager(const QString &path);

    //destructor
    ~DbManager();

    bool isOpen() const;

    void printTables() const;

    //get a vector of tables
    QVector<QString> getTables() const;

    //get a vector of table fields
    QVector<QString> getTableFeilds(const QString &tableName) const;

   // void toXML(const QString &path);
    void toXML();

private:
    QSqlDatabase someDatabase;
};

#endif // DBMANAGER
