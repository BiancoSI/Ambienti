if [ $# 3 -ne 3 ];then
	echo $0 Prende 3 Cartelle 
	exit 
fi
if [ ! ( -d $1 -a -d $2 -a -d $3 ) ];then
	echo $1 o $2 o$3 non è cartella
	exit
fi
cartOrig=$1
cartJava=$2
cartC=$3
files=$(ls $cartOrig)
for f in $files;do
	case $f in
	*.java) cp $cartOrig/$f $cartJava/
	*.c) cp $cartOrig/$f $cartC/
	*) echo -n ""
done

