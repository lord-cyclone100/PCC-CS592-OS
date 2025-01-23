echo "Enter a date in dd/mm/yyyy format"
read date

IFS="/"
set $date

dd=$1
mm=$2
yy=$3

if [ $((yy%400)) -eq 0 ] && [ $((yy%100)) -ne 0 ] || [ $((yy%4)) -eq 0 ] && [ $mm -eq 2 ]
then
    if [ $dd -le 29 ]
    then
        echo "$dd/$mm/$yy is a valid date"
    else
        echo "$dd/$mm/$yy is an invalid date"
    fi
else
    if [ $mm -eq 4 ] || [ $mm -eq 6 ] || [ $mm -eq 9 ] || [ $mm -eq 11 ] && [ $dd -le 30 ]
    then
        echo "$dd/$mm/$yy is a valid date"
    elif [ $mm -eq 1 ] || [ $mm -eq 3 ] || [ $mm -eq 5 ] || [ $mm -eq 7 ] || [ $mm -eq 8 ] || [ $mm -eq 10 ] || [ $mm -eq 12 ] && [ $dd -le 31 ]
    then
        echo "$dd/$mm/$yy is a valid date"
    elif [ $mm -eq 2 ] && [ $dd -le 28 ]
    then
        echo "$dd/$mm/$yy is a valid date"
    else
        echo "$dd/$mm/$yy is an invalid date"
    fi
fi
