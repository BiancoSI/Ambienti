if [ $# -ne 3 ];then
	echo "Errore $0 riceve <file.txt> <CartSorgente> <CartellaDest> "
	exit 1
fi
if [ ! -f $1 -o ! -d $2 -o ! -d $3 ];then
	echo "Errore"
	exit 1
fi
file=$(cat $1)
dirOrg=$2
dirDest=$3
let count=0
let noFile=0
for w in $file;do
	if [ $count -eq 0 ];then
		fileSorg=$w;
		if [ -z $fileSorg ];then
			let noFile=1
		else 
			let noFile=0
		fi
	elif [ $count -eq 1 ];then
		if [ $noFile -eq 0 ];then
			prime=$w
		fi
	elif [ $count -eq 2 ]; then
		if [ $noFile -eq 0 ];then
			ultime=$w
			cat $dirOrg/$fileSorg|head -n $prime > $dirDest/$fileSorg
			cat $dirOrg/$fileSorg|tail -n $ultime >> $dirDest/$fileSorg
		fi
	fi
	let count=($count+1)%3
done

