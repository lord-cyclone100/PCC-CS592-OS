findGCD(){
    a=$1
    b=$2
    while [ $b -ne 0 ]
    do
        temp=$b
        b=$((a%b))
        a=$temp
    done
    echo $a
}

findLCM(){
    a=$1
    b=$2
    if [ $a -gt $b ]
    then
        max=$a
    else
        max=$b
    fi

    while [ 1 ]
    do
        if [ $((max%a)) -eq 0 ] && [ $((max%b)) -eq 0 ]
        then
            echo $max
            break
        else
            max=$((max+1))
        fi
    done
}

gcd=$(findGCD $1 $2)
lcm=$(findLCM $1 $2)
echo "GCD of $1 and $2 : $gcd"
echo "LCM of $1 and $2 : $lcm"