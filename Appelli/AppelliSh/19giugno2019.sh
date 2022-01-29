if [ $# -ne 3 ];then 
	echo Errore $0 prende 3 paramenti
	exit
fi
Origine=$2
Dest=$3
risultati=$(cat $1)
count=0
extCa=cand
extPa=part
for w in $risultati;do
	if [ $count -eq 0 ];then
		nomeC=$(echo $w|sed "s/\."$extCa"$/\.txt/")
	fi
	if [ $count -eq 1 ];then
		nomeP=$(echo $w|sed "s/\."$extPa"$//")
		F=voti_$nomeC
		if [ -f $Origine/$nomeP/$nomeC ];then
			voti=$(cat $Origine/$nomeP/$nomeC|wc -l )
			if [ -f $Dest/$nomeP/$F ];then
				echo File di uscita dei voti di $(echo $nomeC|sed "s/\.txt$//") già esistente.
				exit 1
			else
				cp $Origine/$nomeP/$nomeC $Dest/$nomeP
				echo $voti > $Dest/$nomeP/$F
			fi
		else
			touch $Dest/$nomeP/$nomeC
			echo 0 voti > $Dest/$nomeP/$F
		fi

	fi
	let count=($count+1)%2
done
