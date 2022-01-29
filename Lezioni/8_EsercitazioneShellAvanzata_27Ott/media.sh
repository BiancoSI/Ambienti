if [ $# -lt 1 ]; then
	echo "Uso: $0 <num1><num2><num3>"
	exit 1
fi
let somma=0
for i in $@; do
	let somma=$somma+$i
done
let media=$somma/$#
echo Media=$media
# per semplicità non si considera la media reale, ma si usa la divisione intera standard di shell

