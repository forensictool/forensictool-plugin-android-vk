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

    void toXML();

private:
    QSqlDatabase db;
};

#endif // DBMANAGER
