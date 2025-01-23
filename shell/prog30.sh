echo "Enter number of records you wish to add"
read n
for i in $(seq 1 $n)
do
    echo "Enter roll"
    read roll
    echo "Enter name"
    read name
    echo "Enter marks"
    read marks
    echo "$roll|$name|$marks" >> prog30.txt
done
sort -t "|" -k3 -n "prog30.txt" -o "prog30.txt"