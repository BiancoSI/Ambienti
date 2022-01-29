if [ $# -ne 1 ];then
	echo Errore $0 Riceve un file testo
	exit 1
fi

if [ ! -f $1 ];then 
	echo Errore file $1 non esistente
	exit 1
fi
cont=$(cat $1)
output=Risultato.txt
if [ -f $output ];then
	echo Il file $output sarà sovrascritto
	echo "">$output
fi

for w in $cont;do
	dir=$w
	c=0
	if [ -d $dir ];then
		for f in $(ls $dir|cat );do
			file=$dir/$f
			if [ -f $file -a ! -L $file -a ! -p $file -a ! -S $file ];then
				let c=$c+1
			fi
		done
		echo $dir $c >>$output
	fi
done
