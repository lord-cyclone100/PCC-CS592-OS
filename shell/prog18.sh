lines=`wc -l < prog18a.txt`

echo "Name|Roll|Marks|Grade" > prog18b.txt
for i in $(seq 2 $((lines+1)))
do
    name=`head -n $i prog18a.txt | tail -n 1 | cut -d "|" -f1`
    roll=`head -n $i prog18a.txt | tail -n 1 | cut -d "|" -f2`
    marks=`head -n $i prog18a.txt | tail -n 1 | cut -d "|" -f3`
    if [ $((marks/10)) -ge 9 ]
    then
        grade="O"
    elif [ $((marks/10)) -ge 8 ]
    then
        grade="E"
    elif [ $((marks/10)) -ge 7 ]
    then
        grade="A"
    elif [ $((marks/10)) -ge 6 ]
    then
        grade="B"
    elif [ $((marks/10)) -ge 5 ]
    then
        grade="C"
    elif [ $((marks/10)) -ge 4 ]
    then
        grade="D"
    else
        grade="F"
    fi
    echo "$name|$roll|$marks|$grade" >> prog18b.txt
done