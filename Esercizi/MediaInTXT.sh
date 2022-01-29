if [ $# -ne 5 ];then
	echo $0 riceve 5 parametri interi
	exit 1
fi
media=0
for x in $@;do
	if [ $x -lt 0 ];then
		echo $0 riceve 5 Parametri interi
		exit 1
	else
		let media=$media+$x
	fi
done
let media=$media/$#
echo -n "Digitare una cartella. I file .txt della Cartella conterrano la media >>"
read dir
if [ ! -d $dir ];then
	echo Dopo 5 interi $0 riceve una Cartella
	exit 1
fi
myFiles=$(ls $dir)
for file in $myFiles;do
	case $file in
	*.txt) echo $media>>$dir/$file;;
	*);;
	esac
done

