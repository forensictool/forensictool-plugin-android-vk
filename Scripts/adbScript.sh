#! /bin/bash

adb root
adbState=`adb get-state`
if [[ "$adbState" = "device" ]]
then
appList=`adb shell pm list packages -f > appList.txt`  # Все установленные приложения на смартфоне
neededApp="vkontakte"
grepInfo=`grep "$neededApp" appList.txt` # Поиск нужного приложения
if [[ "$grepInfo" != "" ]]
then 
	echo "Есть такое приложение!"
	mkdir Pulled
	mv appList.txt Pulled
	cd Pulled
	adb backup -f vkontakte.ab com.vkontakte.android
else 
	echo "Нет такого приложения!"
	rm appList.txt
	exit 1
fi
else
	echo "Подключите устройство!"
	exit 1
fi
