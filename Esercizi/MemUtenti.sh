if [ $# -ne 1 -o ! -f $1 ];then
	echo $0 riceve un file 
	exit 1
fi
utenti=$(who -q|head -n 1)
file=$1
for u in $utenti;do
	processi=$(ps -u $u|tr -s " " " "|cut -d " " -f 5|sort|uniq)
	echo "Processi relativi all'utente $u">>$file
	for p in $processi;do
		echo $p>>$file
	done
	echo "............">>$file
done

