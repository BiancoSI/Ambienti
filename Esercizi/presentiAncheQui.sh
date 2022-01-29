if [ $# -ne 1 -o ! -f $1 ];then
	echo $0 riceve un file contenete un elenco di file
	exit 1
fi
contenuto=$(cat $1)
numeroFile=0
for f in $contenuto;do
	calcolo=$(ls .|grep -wc "^$f$")
	if [ $calcolo -gt 0 ];then
		let numeroFile=$numeroFile+1
	fi
done
echo numero di file $numeroFile
