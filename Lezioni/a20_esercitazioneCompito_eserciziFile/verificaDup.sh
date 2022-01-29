if [ $# -ne 2 ];then
    echo "Uso: $0 <file_cartelle><file_output>"
    exit 1
fi
if [ ! -f $1 ]; then
    echo "File $1 non esiste"
    exit 2
fi

if [  -f $2 ]; then
    echo "File $2 esiste già, lo cancello"
    echo -n >$2
fi
istruzioni=$1
output=$2
contenuto=$(cat $istruzioni)
count=0
for i in $contenuto;do 
  if [ $count -eq 0 ]; then
    primaCart=$i
  else
    secondaCart=$i
    #verifica duplicati
    files=$(ls $primaCart 2>/dev/null)
    for miofile in $files; do
          if [ -f $secondaCart/$miofile ];then
            #trovato file duplicato
            echo "$miofile duplicato nella cartella $secondaCart">> $output
          fi             
    done
  fi
  let count=($count+1)%2
done