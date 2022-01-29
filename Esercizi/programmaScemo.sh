num=100
file=$1
while [ $num -gt 0 ];do
	echo $num >> $file
	let num=$num-1
done
