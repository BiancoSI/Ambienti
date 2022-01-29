if [ $# -eq 0 ];then
	exit 1;
fi
for d in $@;do
	if [ ! -d $d ];then
		echo Errore $d non è una cartella o non esiste
	else
		echo -n "Serie di estensioni da eliminare nella cartella $d; Terminare con END >>"
		read ext
		for e in $ext;do
			if [ $e = "END" ];then
				echo "Fine Cartella $d"
				break
			else
				contEl=$(ls  $d/*.$e 2>/dev/null|wc -w)
				rm $d/*.$e 2>/dev/null
				echo Rimossi $contEl .$e
			fi
		done
	fi
done
