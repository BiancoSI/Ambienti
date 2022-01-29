if [ $# -ne 0 ];then
	echo Errore $0 riceve 2 parametri "<file testo> <DirOutput>"
	exit 1
fi
if [ ! -f $1 -o ! -d $2 ];then
	echo Errore $1 e/o $2 non esiste
	exit 1
fi

output=$2
fileTe=$(cat $1)
count=0
for w in $fileTe;do
	if [ $count -eq 0 ];then
		dir=$w
		if[ ! -d  $dir ];then
			let count=-3
		fi
	elif [ $count -eq 1 ];then
		file=$w
		presente=$(ls $dir|grep -c "^$file$")
		if [ $presente -eq 0 ];then
			let count=-2
		fi
	elif [ $count -eq 2 ];then
		ext=$w
		fileExt=$(echo $file|sed -n"s/.*\.//")
		if [ $ext -ne $fileExt ];then
			nuovoNome=$(echo $file|sed -n"s/\..*$/\.$ext/")
			cp $dir/$file $output/$nuovoNome
		fi
	fi
	let count=$count+1
done

