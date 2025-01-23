checkPrime(){
    a=$1
    count=0
    for i in $(seq 1 $a)
    do
        if [ $((a%i)) -eq 0 ]
        then
            count=$((count+1))
        fi
    done
    if [ $count -eq 2 ]
    then
        echo "$a is a prime number"
    fi
}

for i in $(seq $1 $2)
do
    (checkPrime $i)
done