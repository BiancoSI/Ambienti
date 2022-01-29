if [ $# -lt 3 ];then
	echo "Uso: <cartOrigine><cartJava><cartC>"
	exit 1
fi
if [ ! \( -d $1 -a -d $2 -a -d $3 \) ];then
	echo " almeno uno di tre parametri non è una cartella"
	exit 1
fi

mieiFiles=$(ls $1)
for file in $mieiFiles;do
	case $file in
		  *.c)      cp $1/$file $3/ ;;
		  *.java)   cp $1/$file $2/ ;;
		  *) echo "File $file non copiato";;
		esac
done 

