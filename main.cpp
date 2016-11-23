#include <QCoreApplication>
#include <iostream>
#include <dbmanager.h>


static const QString path = "/home/alexey/testbackup/1/apps/com.vkontakte.android/db/vk.db";


int main(){
    DbManager db(path);

    if (db.isOpen()) {
        db.printTables();
        db.toXML();
    }
    else {
        std::cout << "Database is not open.";
    }
    return 0;
}
