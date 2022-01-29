if [ ! -f $1 -o $# -le 0 ];then
	echo $0 riceve un file
	exit 1
fi
numeroFile=$(cat $1 |wc -l)
echo numero di file $numeroFile
