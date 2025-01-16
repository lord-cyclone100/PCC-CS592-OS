#Write a shell script to calculate the value of the series: x + x^2/2! + x^4/4! +...

calculateFactorial(){
	fact=1
	while [ $val -gt 1 ]
	do
		fact=$((fact*$num))
		num=$((num-1))
	done
	echo $fact
}

calculatePower(){
	val=$(i-1)
	pow=$(echo "$x^$val"|bc)
	echo $pow
}

echo "Enter the value of x:"
read x
echo "Enter the number of terms:"
read num
sum=0

for i in $(seq 1 $num)
do
	val=$(i-1)
	s=$(calculateFactorial $val)
	p=$(calculatePower $val)
	sum=$((sum+))
done

#s=$(calculateFactorial $num)
#echo $s
