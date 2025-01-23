printFibo(){
    n=$1
    if [ $n -eq 0 ]
    then
        echo $n
    elif [ $n -eq 1 ]
    then
        echo $n
    else
        a=$(printFibo $((n-1)))
        b=$(printFibo $((n-2)))
        echo $((a+b))
    fi
}

echo "Enter the number of terms"
read n

echo -n "" > prog4.txt

for i in $(seq 0 $((n-1)))
do
    term=$(printFibo $i)
    echo -n "$term " >> prog4.txt
done