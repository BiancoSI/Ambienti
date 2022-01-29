if [ $# -ne 1 -o ! -f $1 ];then 
	echo Errore $0 prende un file
	exit 1
fi
file=$1
lista=$(ls)
presenti=0
for f in $lista;do
	count=$(grep -wc "$f" $file)
	if [ $count -gt 0 ];then
		let presenti=$presenti+1
	fi
done
echo Presenti $presenti file "in" $(pwd)


