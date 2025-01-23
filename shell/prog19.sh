lines=`wc -l < prog19a.txt`
echo "day_name|Weather" > prog19b.txt
for i in $(seq 2 $((lines+1)))
do
    day=`head -n $i prog19a.txt | tail -n 1 | cut -d "|" -f1`
    temp=`head -n $i prog19a.txt | tail -n 1 | cut -d "|" -f2`
    if [ $temp -lt 15 ]
    then
        weather="Very Cold"
    elif [ $temp -ge 15 ] && [ $temp -lt 25 ]
    then
        weather="Cold"
    elif [ $temp -ge 25 ] && [ $temp -lt 35 ]
    then
        weather="Hot"
    else
        weather="Very Hot"
    fi
    echo "$day|$weather" >> prog19b.txt
done
