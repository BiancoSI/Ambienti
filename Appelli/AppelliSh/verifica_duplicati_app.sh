if [ $# -ne 2 ];then
	echo "Errore $0 riceve 2 FileTesto"
	exit 1
fi
if [ ! -f $1 -o ! -f $2 ];then
	echo "Errore file di testo non esistente/i"
	exit 1
fi
if [ -f $2 ];then
	echo -n "">$2
fi
contf1=$(cat $1)
output=$2;
count=0

for dir in $contf1;do
	if [ $count -eq 0 ];then
		dirA=$(ls $dir)
	fi
	if [ $count -eq 1 ];then
		dirB=$dir
		if[ -d $dirA -a -d $dirB ];then
			for f in $(ls $dirA 2>/dev/null);do

				if [ -f $dirB/$f ];then
					echo $f $dirB >> $output
				fi

			done
		fi
	fi
	let count=($count+1)%2
done
