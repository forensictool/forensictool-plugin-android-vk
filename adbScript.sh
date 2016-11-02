#! /bin/bash

adb root
adbState=`adb get-state`
if [[ "$adbState" = "device" ]]
then
appList=`adb shell pm list packages -f > appList.txt`  # Все установленные приложения на смартфоне
echo "Введите искомое приложение: "
	read neededApp
grepInfo=`grep "$neededApp" appList.txt` # Поиск нужного приложения
if [[ "$grepInfo" != "" ]]
then 
	echo "Есть такое приложение!"
	echo "Введите директорию, которую необходимо запулить: "
	read dir_name
	mkdir Pulling
	echo `adb pull $dir_name Pulling`

else 
	echo "Нет такого приложения!"
	exit 1
fi
else
	echo "Подключите устройство!"
	exit 1
fi
