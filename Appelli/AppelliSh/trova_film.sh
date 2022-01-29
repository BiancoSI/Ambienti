if [ $# -ne 2 ];then
	echo Errore $0 riceve una cartella e un file.
	exit 1
fi
if [ ! -d $1 ];then
	echo Errore $1 non è una directory o non esiste
	exit 1
fi
if [ ! -f $2 ];then
	echo Errore $2 non è un file o non esiste
	exit 1
fi
if [ -f output.txt ];then
	echo File di uscita già esistente sarà sovrascritto
	echo -n ""> output.txt
fi

dir=$1
file=$2
count=0
cont=$(cat $file)

for w in $cont;do
	if [ $count -eq 0 ];then
		nomeFilm=$w
	fi
	if [ $count -eq 1 ];then
		anno=$w
	fi
	if [ $count -eq 2 ];then
		ext=$w
		completo=$nomeFilm.$ext
		if [ -d $dir/$anno ];then
			if [ -f $dir/$anno/$completo ];then
				echo $completo $anno >> output.txt
			else
				for d in $(ls $dir);do
					if [ -f $dir/$d/$completo ];then
						echo "Errore: $completo $d invece di $anno">>output.txt
					fi
				done
			fi
		fi
	fi
	let count=($count+1)%3;
done
