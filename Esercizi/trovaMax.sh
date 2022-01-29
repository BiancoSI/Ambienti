if [ $# -le 0 ];then
	echo Errore almeno un numero
	exit 1
fi
max=$1
for n in $@;do
	if [ $max -lt $n ];then
		max=$n
	fi
done
echo il maggiore tra $@ è $max
