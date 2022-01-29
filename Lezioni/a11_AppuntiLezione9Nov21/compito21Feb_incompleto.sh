#Scrivere un programma shell (verifica_istruzioni.sh) che riceva come parametri un file di testo (istruzioni.txt) e 2 cartelle cartA cartB e dovrà seguire le istruzioni contenute nel file istruzioni.txt
# per copiare file da cartellaA a cartellaB.
#Esempio d’uso sarà : verifica_istruzioni.sh istruzioni.txt cartA cartB.
#Ogni riga del file istruzioni.txt sarà fatta così: <nome_file> <num_righe_iniziali> <num_righe_finali>
#esempio: pippo.txt 7 5
#In questo caso bisognerà copiare le prime 7 righe e le ultime 5 del file pippo.txt contenuto in cartA in cartB
# (con lo stesso nome, o se si riesce meglio con il nome pippo_7_5.txt)
#Gestire anche il controllo degli errori (parametri insufficienti, file di output già esistente, cartella inesistente, ecc..).
if [ $# -ne 3 ]; then
	echo "Uso: $0 <file_istr><cartOr><cartDest>"
	exit 1
fi
if [ ! -f $1 ]; then
	echo" $1 deve essere un file"
	exit 2
fi
cartA=$2
cartB=$3
istr=$1
params=$(cat $1)    #  topo.txt 3 5  pippo.txt 4 6
count=0
for i in $params;do 
	if [ $count -eq 0 ]; then
		nomeFile=$i
	elif  [ $count -eq 1 ]; then
		par1=$i
	elif [ $count -eq 2 ]; then
		par2=$i
		echo "$nomeFile $par1 $par2"
		head -n $par1 $cartA/$nomeFile > tmp1.txt
		tail -n $par2 $cartA/$nomeFile > tmp2.txt
		cat tmp1.txt tmp2.txt > $cartB/$nomeFile
	fi
	let count=($count+1)%3

done 




