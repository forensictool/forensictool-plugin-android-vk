#ifndef DBMANAGER
#define DBMANAGER

#include <QSqlDatabase>

class DbManager
{
public:
    //constructor; path - path to db
    DbManager(const QString &path);

    //destructor
    ~DbManager();

    bool isOpen() const;

    void printTables();

    void toXML();

private:
    QSqlDatabase db;
};

#endif // DBMANAGER
