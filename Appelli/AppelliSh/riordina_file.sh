if [ $# -ne 3 ];then
	echo $0 riceve file.txt Dir1 Dir2
	exit 1
fi
if [ ! -f $1 -o ! -d $2 -o ! -d $3 ];then
	echo Attenzione $1 e/o $2 e/o $3 non esiste/esistono
	exit 1
fi
pre=riordina
fileLog=$1
dirO=$2
dirD=$3
for dir in $dirO;do
	for file in $dir;do
		ext=$(echo $file|sed "s/\./\n/"|tail -n 1)
		dird=$pre$ext
		if [ $ext == "txt" ];then
			fileTxt=$fileTxt" "$file
		elif [ $ext == "doc" ];then
			fileDoc=$fileDoc" "$file
		elif [ $ext == "xls" ];then
			fileXls=$fileXls" "$file
		elif [ $ext == "java" ];then
			fileJava=$fileJava" "$file
		fi
		cp $file $dirD/$dird
	done
done
echo $fileDoc >>$filelog
echo $fileTxt >>$fileLog
echo $fileCls >>$fileLog
echo $fileJava >>$fileLog
