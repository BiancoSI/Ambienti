if [ $# -ne 3 ];then
	echo $0 riceve 3 parametri "<ext1> <xt2> <dir>	"
	exit 1
fi
if [ ! -d $3 ];then
	echo $3 non esiste
	exit 1
fi

ext1=$1
ext2=$2
dir=$(ls $3|grep ".*\."$ext1"$");
count=0
sop=0
for f in $dir;do
	file_ext2=$(echo $f| sed "s/\."$ext1"$/\.$ext2/")
	if [ ! -f $3/$file_ext2 ];then
		rm $3/$f
		let count=$count+1
	fi
done
sop=$(ls $3| grep -c ".*\."$ext1"$")
echo Eliminati $count file .$ext1
echo Presenti $sop file $ext1 e $ext2
