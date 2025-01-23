echo "Enter the number of records you wish to add"
read n
for i in $(seq 1 $n)
do
    echo "Enter student roll"
    read roll
    echo "Enter student name"
    read name
    echo "Enter student marks"
    read marks

    echo "$roll|$name|$marks" >> prog23.txt
done