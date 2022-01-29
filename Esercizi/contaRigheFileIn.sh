if [ $# -ne 1 -o ! -d $1 ];then
	echo Errore. Passare una directory
	exit 1
fi
dir=$1
lista=$(ls $dir)
for f in $lista;do
	if [ -f $f ];then
		echo Nome">>"$f
		righe=$(cat $f|wc -l )
		echo Numero di Righe">>"$righe
	fi
done

