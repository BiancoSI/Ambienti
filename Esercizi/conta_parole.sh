if [ $# -ne 2  ];then
    echo "$0 Prende una parola e un file"
    exit
fi
if [ ! -f $2 ];then
	echo "$0 Prende una parola e un file"
	exit
fi
list=$(cat $2)
parola=$1
count=0
for w in $list;do
	if [ $w = $parola ];then
		let count=$count+1
	fi
done
echo "La parola $parola compare in $file $count volte"
