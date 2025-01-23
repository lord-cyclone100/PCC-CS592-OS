echo "Enter your dob in dd/mm/yyyy format"
read dob

IFS="/"
set $dob

dd=$1
mm=$2
yy=$3

d=$(date +%d)
m=$(date +%m)
y=$(date +%Y)

yearNumber=$((y-yy))
monthNumber=$((m-mm))
dayNumber=$((d-dd))

if [ $dd -gt $d ]
then
    monthNumber=$((monthNumber-1))
    dayNumber=$((dayNumber+30))
fi

if [ $mm -gt $m ]
then
    yearNumber=$((yearNumber-1))
    monthNumber=$((monthNumber+12))
fi

echo "You are currently $yearNumber years $monthNumber months and $dayNumber days old"