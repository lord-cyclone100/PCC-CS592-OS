c=`wc -l prog10.txt | cut -d " " -f1`
marks=0
name=""
roll=0
for i in $(seq 2 $((c+1)))
do
    m=`head -n $i prog10.txt | tail -n 1 | cut -d "|" -f3`
    r=`head -n $i prog10.txt | tail -n 1 | cut -d "|" -f1`
    n=`head -n $i prog10.txt | tail -n 1 | cut -d "|" -f2`
    if [ $m -gt $marks ]
    then
        marks=$m
        name=$n
        roll=$r
    fi
done
echo "$name got with roll $roll got the highest marks. Marks : $marks"