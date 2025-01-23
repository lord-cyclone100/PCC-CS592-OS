directory="./prog28"

files=`ls -p $directory | grep -v / | wc -l`
l=$(ls -S $directory | head -n 1)
echo $l