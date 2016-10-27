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

    void printTables() const;

private:
    QSqlDatabase someDatabase;
};

#endif // DBMANAGER
