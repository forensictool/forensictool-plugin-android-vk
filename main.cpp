#include <QCoreApplication>
#include <iostream>
#include <dbmanager.h>
#include <QFile>



int main(){


    system("../forensictool-plugin-android-vk/Scripts/adbScript.sh"); // дергаем базу
    system("../forensictool-plugin-android-vk/Scripts/unAB.sh 2"); // затариваем-растариваем базу
    static const QString path = "../forensictool-plugin-android-vk/Scripts/Pulled/apps/com.vkontakte.android/db/vk.db";


    DbManager db(path);

    if (db.isOpen()) {
        db.printTables();
       // db.toXML();
    }
    else {
        std::cout << "Database is not open.";
    }
    return 0;
}
