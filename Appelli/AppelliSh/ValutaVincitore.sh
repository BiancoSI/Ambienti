if [ $# -ne 2 ];then
	echo $0 riceve dir e file
	exit 1
fi
if [ ! -d $1 ];then
	echo Cartella $1 non esistente
	exit 1
fi
if [ ! -f $2 ];then
	echo File $2 non esistente 
	exit 1
fi

dir=$1
filevinc=$2
vinc=""
max=-1

for c in $(ls $dir);do
	numvoti=0
	for v in $(cat $dir/$c);do
		let numvoti=$numvoti+$v
	done
	if [ $numvoti -gt $max ];then
		max=$numvoti
		vinc=$c
	fi
done
echo $(echo $vinc| sed "s/\.txt$//" ) $max punti >>$filevinc

