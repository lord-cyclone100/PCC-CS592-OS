lines=`wc -l < prog26a.txt`

echo "Enter the name of the student to delete record"
read name
echo "Roll|Name|Marks" > prog26b.txt
for i in $(seq 2 $((lines+1)))
do
    r=`head -n $i prog26a.txt | tail -n 1 | cut -d "|" -f1`
    n=`head -n $i prog26a.txt | tail -n 1 | cut -d "|" -f2`
    m=`head -n $i prog26a.txt | tail -n 1 | cut -d "|" -f3`
    if [ "$n" = "$name" ]
    then
        continue
    else
        echo "$r|$n|$m" >> prog26b.txt
    fi
done
mv prog26b.txt prog26a.txt