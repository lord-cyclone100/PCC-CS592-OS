checkLeapYear(){
    a=$1
    if [ $((a%400)) -eq 0 ]
    then
        echo "$a is a leap year"
    elif [ $((a%100)) -eq 0 ]
    then
        echo "$a is not a leap year"
    elif [ $((a%4)) -eq 0 ]
    then
        echo "$a is a leap year"
    else
        echo "$a is not a leap year"
    fi
}

for i in "$@"
do
    (checkLeapYear $i)
done