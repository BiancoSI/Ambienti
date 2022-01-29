if [ $# -ne 2 ];then
	echo Errore
	exit 1
fi
if [ ! -d $1 -o ! -d $2 ];then
	echo Errore
	exit 1
fi
dirS=$1
dirD=$2
for f in $(ls $dirS);do
	if [ $(echo $f |grep -c "*\.exe") -gt 0  ];then
		nuovoNome=$(echo $f|sed -n"s/\.exe/\.sh/")
		cp $dirS/$f $dirD/$nuovoNome
	elif [ -d $dirS/$f ];then
		mkdir $dirD/$f
		for ele in $(ls $dirS/$f);do
			if [ $(echo $ele|grep -c "*\.exe") -gt 0 ];then
				nuovoNome=$(echo $ele| sed -n "s/\.exe/\.sh")
				cp $dirS/$f/$ele $dirD/$f/$nuovoNome
			elif [ -d $dirS/$f/$ele ];then
				mkdir $dirD/$f/$ele
			else cp $dirS/$f/$ele $dirD/$f
			fi
		done
	else cp $dirS/$f $dirD
	fi
done

