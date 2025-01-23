#Write a shell script to calculate the value of the series: x + x^2/2! + x^4/4! +...

calculateFactorial(){
	val=$1
	fact=1
	while [ $val -gt 1 ]
	do
		fact=$((fact*$num))
		val=$((val-1))
	done
	echo $fact
}

calculatePower(){
	val1=$1
	val2=$2
	pow=$(echo "$val1^$val2"|bc)
	echo $pow
}

echo "Enter the value of x:"
read x
echo "Enter the number of terms:"
read num
sum=0

for i in $(seq 0 $((num-1)))
do
	power1=$(calculatePower 2 $i)
	power2=$(calculatePower $x $power1)
	f=$(calculateFactorial $power1)
	div=$(echo "scale=3; $power2/$f" | bc)
	sum=$(echo "scale=3; $sum+$div" | bc)
done
echo "Sum : $sum"
