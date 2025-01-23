lines=`wc -l < prog15a.txt`
echo $((65/10))
echo "Name|Roll|Marks|Grade" > prog15b.txt
for i in $(seq 2 $((lines+1)))
do
    name=`head -n $i prog15a.txt | tail -n 1 | cut -d "|" -f1`
    roll=`head -n $i prog15a.txt | tail -n 1 | cut -d "|" -f2`
    marks=`head -n $i prog15a.txt | tail -n 1 | cut -d "|" -f3`
    case $((marks/10)) in
    10)
        grade="O"
    ;;
    9)
        grade="O"
    ;;
    8)
        grade="E"
    ;;
    7)
        grade="A"
    ;;
    6)
        grade="B"
    ;;
    5)
        grade="C"
    ;;
    4)
        grade="D"
    ;;
    *)
        grade="F"
    ;;
    esac
    echo "$name|$roll|$marks|$grade" >> prog15b.txt
done