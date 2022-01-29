if [ $# -ne 3 ];then
	echo $0 riceve 3 parametri "<File.txt><DirA><DirB>"
	exit 1
fi

if [ ! -f $1 ];then
	echo File di testo inesistente.
	exit 1
fi
if [ ! -d $2 -o ! -d $3 ];then
	echo Cartelle/a inesistente.
	exit 1
fi
touch FileMusica.txt
cont=$(cat $1)
count=0
dirA=$2
dirB=$3
for w in $cont;do
	if [ $count -eq 0 ];then
		a=$w
		ext1=$(echo $w| sed "s/.*\.//")
		nomef=$(echo $w|sed "s/\."$ext1"$//")		
	fi
	if [ $count -eq 1 ];then
		ext=$w;
		file=$nomef.$ext
		if [ -f $dirA/$file ];then
			nuovoF=$a
			if [ ! -f $dirB/$nuovoF ];then
				cp $dirA/$file $dirB/$nuovoF
				if [ ! -f $ext1 ];then
					echo $ext1 >>FileMusica.txt
					touch $ext1
				fi
				echo "-" >> $ext1
			fi
		fi
	fi
	let count=($count+1)%2
done
for f in $(cat FileMusica.txt);do
	echo Convertiti in $f $(cat $f|wc -l) files
	rm $f
done
rm FileMusica.txt
