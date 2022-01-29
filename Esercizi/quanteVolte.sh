if [ $# -ne 2 -o ! -f $1 ];then
	echo Errore
	exit 1
fi
file=$1
word=$2
occorrenze=0
for w in $(cat $file);do
	if [ $w = $word ];then
		let occorrenze=$occorrenze+1
	fi
done
echo Nel file $file sono presenti $occorrenze occorrenza/e di $word.

