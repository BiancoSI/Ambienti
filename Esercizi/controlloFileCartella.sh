if [ $# -ne 2 ];then
	echo $0 riceve "<file>" e "<cartella>" e verifica che "<file>" sia in "<cartella>".
	exit
fi
if [ ! -f $1 -o ! -d $2 ];then
	echo $0 riceve "<file>" e "<cartella>" e verifica che "<file>" sia in "<cartella>"
	exit
#elif [ ! -d $2 ];then 
#	echo $0 riceve "<file>" e "<cartella>" e verifica che "<file>" sia in "<cartella>"
#	exit
fi

file=$1
cartella=$2
num=$(ls $cartella|grep -c $file )
if [ $num -eq 0 ];then
	echo file $file non presente "in" $cartella
	exit
fi
echo file $file presente "in" $cartella

