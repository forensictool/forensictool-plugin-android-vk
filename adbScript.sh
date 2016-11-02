#! /bin/bash

adb root
adbState=`adb get-state`
appList=`adb shell pm list packages -f > appList.txt`
echo "Введите искомое приложение: "
	read neededApp
grepInfo=`grep "$neededApp" appList.txt`
if [[ "$adbState" = "device" ]]
if [[ "$grepInfo" != "" ]]
then 
	echo "Есть такое приложение!"
else 
	echo "Нет такого приложения!"
fi
then
	echo "Введите директорию, которую необходимо запулить: "
	read dir_name
	mkdir Pulling
	echo `adb pull $dir_name Pulling`
else
	echo "Подключите устройство!"
	exit 1
fi
