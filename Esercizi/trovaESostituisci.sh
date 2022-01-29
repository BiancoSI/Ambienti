if [ $# -ne 2 ];then
	echo "$0 Prende <parola><file>"
	exit
fi
if [ ! -f $2 ];then
	echo "File inesistente"
	exit
fi
echo -n "Parola con cui sostituire >>"
read daSost
list=$(cat $2)
parola=$1
touch output.txt
for w in $list;do
	if [ $w = $parola ];then
		echo $daSost>>output.txt
	else
		echo $parola>>output.txt
	fi
done

mv output.txt $2
