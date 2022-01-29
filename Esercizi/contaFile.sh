if [ $# -ne 1 -o ! -f $1 ];then
 	echo $0 Riceve un solo File con coppie "<file> <Cartella>"
	exit 1
fi
file=$(cat $1)
count=0
ris=0
for x in $file;do
	if [ $count -eq 0 ];then
		nomfile=$x
	else
		nomdir=$x
		if [ $(ls $nomdir|cat|grep -c $nomfile) -gt 0 ];then
			let ris=$ris+1
		fi
	fi
	let count=($count+1)%2
done
echo Numero di Riscontri $ris

