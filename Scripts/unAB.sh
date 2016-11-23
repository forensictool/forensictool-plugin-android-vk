#! /bin/bash

cd Pulled
echo "Есть три способа разархивировать полученный бэкап."
echo "Введите 1 для использования python"
echo "Введите 2 для использования java"
echo "Введите 3 для использования openSSL"
read method
echo "$method"

case $method in
1 )
dd if=vkontakte.ab bs=1 skip=24 | python -c "import zlib,sys;sys.stdout.write(zlib.decompress(sys.stdin.read()))" > vkontakte.tar
	;;
2 ) 
java -jar ../android-backup-extractor-20160710-bin/abe.jar unpack vkontakte.ab vkontakte.tar
	;;	
3 ) 
dd if=data.ab bs=1 skip=24 | openssl zlib -d | tar -xvf
	;;
*) echo "Введённые данные некорректны!"
esac
tar xvf vkontakte.tar
