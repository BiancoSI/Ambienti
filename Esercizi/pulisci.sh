if [ $# -ne 1 ];then
	echo Errore passare una cartella
	exit 1
fi
dir=$1
if [ ! -d $dir ];then
	echo $0 prendere una directory e ne pulisce il contenuto
	exit 1
fi
echo -n Estensione dei file da eliminare ">>"
read ext
cartellaCorrente=.
cd $dir
rm *.$ext
cd $cartellaCorrente

