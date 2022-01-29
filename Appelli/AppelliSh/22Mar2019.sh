if [ $# -ne 3 ];then
	echo $0 Riceve "<numero><numero><dir>"
	exit 1
fi
if [ $1 -lt 0 -o $2 -lt 0 ];then
	echo $0 riceve numeri positivi
	exit 1
fi

if [ ! -d $3 ];then
	echo $3 non esistente
	exit 1
fi

dir=$3
n1=$1
n2=$2
i=0
ext=bak
mul=0

while [ $i -ne $n2 ];do
	let mul=$mul+$n1
	let i=$i+1
done

for f in $(ls $dir| grep "\.txt$");do
	echo $mul >> $dir/$f
	newName=$(echo $f|sed "s/\.txt$/\."$ext"/")
	if [ -f $dir/$newName ];then
		echo File di output già esistente $newName
		exit 1
	else
		mv $dir/$f $dir/$newName
	fi
done
