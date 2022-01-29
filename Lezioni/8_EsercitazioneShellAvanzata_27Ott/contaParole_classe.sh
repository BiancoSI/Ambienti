if [ $# -ne 2 ]; then
	echo "Uso: $0 <parola><nomeFile>"
	exit 1
fi
parCerc=$1
nomeFile=$2
conta=0
contenuto=$(cat $nomeFile)
for parola in $contenuto; do
	if [ $parola = $parCerc ]; then
		let conta=$conta+1
	fi
done
echo "Trovate $conta parole=$parCerc"
