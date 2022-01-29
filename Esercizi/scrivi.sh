if [ $# -ne 2 ];then
	echo I parametri non sono 2 riprovare
	echo $0 prendere un file e un numero
	exit 1
fi
file=$1
num=$2
if [ ! -f $file -o $num -lt 0 ];then
	echo Errore $0 prende un file e un numero positivo
	exit 1
fi
echo -n Immettere parola da scrivere "in" $file $num volte" >>"
read string
while [ $num -gt 0 ];do
	echo $string >>$file
	let num=$num-1
done

