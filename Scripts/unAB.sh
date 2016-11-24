#! /bin/bash

method=$1

case $method in
1 )
dd if=vkontakte.ab bs=1 skip=24 | python -c "import zlib,sys;sys.stdout.write(zlib.decompress(sys.stdin.read()))" > vkontakte.tar
	;;
2 ) 
java -jar ../forensictool-plugin-android-vk/Scripts/android-backup-extractor-20160710-bin/abe.jar unpack ../forensictool-plugin-android-vk/Scripts/Pulled/vkontakte.ab ../forensictool-plugin-android-vk/Scripts/Pulled/vkontakte.tar
	;;	
3 ) 
dd if=data.ab bs=1 skip=24 | openssl zlib -d | tar -xvf
	;;
*) echo "Введённые данные некорректны!"
esac 
cd ../forensictool-plugin-android-vk/Scripts/Pulled/
tar xvf vkontakte.tar
