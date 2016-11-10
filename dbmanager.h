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

   // void toXML(const QString &path);
    void toXML();

private:
    QSqlDatabase someDatabase;
};

#endif // DBMANAGER
