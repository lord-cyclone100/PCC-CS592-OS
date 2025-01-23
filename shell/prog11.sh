count=`wc -l < prog11.txt`
largest=-999999
smallest=999999
for i in $(seq 1 $((count+1)))
do
    num=`head -n $i prog11.txt | tail -n 1`
    if [ $num -gt $largest ]
    then
        largest=$num
    fi

    if [ $num -lt $smallest ]
    then
        smallest=$num
    fi
done
echo "Largest number $largest"
echo "Smallest number $smallest"