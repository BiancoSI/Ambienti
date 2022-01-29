echo -n Digitare una serie di File separati da spazio"-->"
read files
presenti=0
f_dir=$(ls|cat)
echo $f_dir
for f in $files;do
	for p in $(ls);do
		if [ $f = $p ];then
			let presenti=$presenti+1
		fi
	done
done
echo Presenti "in" . ">>"  $presenti



