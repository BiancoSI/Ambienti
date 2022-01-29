if [ $# -ne 2 ];then
	echo Errore $0 riceve directori file di testo
	exit 1
fi
if [ ! -f $2 -o ! -d $1 ];then
	echo Errore file e/o cartella inesistente
	exit 1
fi
dir=$1
file=$(cat $2)
count=0

for i in $file;do
	if [ $count -eq 0 ];then
		dirDest=$i
	else
		ext=$i
		if [ -d $dirDest ];then
			file_with_ext=$(ls $dir)
			for f in $file_with_ext;do
				cp $f $dirDest
				newN=echo $f|sed "s/\.$ext/\.bak/"
				mv $dirDest/$f $dirDest/$newN
			done
		fi
	fi
	let count=($count+1)%2
done

