countDigit(){
    a=$1
    count=0
    while [ $a -ne 0 ]
    do
        count=$((count+1))
        a=$((a/10))
    done
    echo $count
}

checkArmstrong(){
    b=$1
    d=$(countDigit $b)
    sum=0
    while [ $b -ne 0 ]
    do
        rem=$((b%10))
        pow=$(echo "$rem ^ $d"|bc)
        sum=$((sum+pow))
        b=$((b/10))
    done
    echo $sum
}

for i in "$@"
do
    c=$(checkArmstrong $i)
    if [ $c -eq $i ]
    then
        echo "$i is an Armstrong number"
    else
        echo "$i is not an Armstrong number"
    fi
done