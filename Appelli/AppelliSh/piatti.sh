if [ $# -ne 3 ];then
	echo Errore $0 prende DirA DirB file.txt
	exit 1
fi
if [ ! -d $1 -o ! -d $2 ];then
	echo Errore $1 e/o $2 non esistono/esiste
	exit 1
fi
if [ ! -f $3 ];then
	echo Errore $3 non esiste
	exit 1
fi

if [ -f Piatti ];then
	echo -n > Piatti
else
	touch Piatti
fi

dirA=$1 
dirB=$2
piatti=$(cat $3)
count=0
for e in $piatti;do
	if [ $count -eq 0 ];then
		nomePiatto=$e

	else 
		rist_prezzo=$e
		if [ -f $dirA/$nomePiatto.doc -a -f $dirA/$rist_prezzo ];then
			nuovoF=$nomePiatto.txt
			if [ ! -f $nuovoF ];then
				echo $nomePiatto>> Piatti
			fi
			echo $(cat $rist_prezzo)>>$nuovoF


		fi
	fi
done
