dir1="./prog29a"
dir2="./prog29b"

file1=`ls -p $dir1 | grep -v / | wc -l`
file2=`ls -p $dir2 | grep -v / | wc -l`

if [ $file1 -gt $file2 ]
then
    echo "$dir1 has greater number of files"
elif [ $file2 -gt $file1 ]
then
    echo "$dir2 has greater number of files"
else
    echo "$dir1 and $dir2 have equal number of files"
fi
