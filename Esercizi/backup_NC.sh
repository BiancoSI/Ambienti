if [ $# -ne 2 -o ! -d $1 -o ! -d $2 ];then
	echo Errore
	exit 1
fi
dirOr=$1
dirDe=$2
listaF=$(ls $dirOr/*.java)
for f in $listaF;do
	touch $dirDe/$f
	$(cat $f|grep -v "//" >>$dirDe/$f)
done

