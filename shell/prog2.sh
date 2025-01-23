#Write a shell script to calculate the value of the series: 1 + (x/2)^2 – (x/2)^3 + (x/2)^4 – (x/2)^5+...

echo "Enter the value of n"
read n
echo "Enter the value of x"
read x
x=$(echo "scale=3; $x/2" | bc)
sum=1

for i in $(seq 1 $n)
do
    pow=$(echo "scale=3; $x ^ $((i+1))" | bc)
    pow=$(echo "scale=3; $pow * (-1)^$((i+1))" | bc)
    sum=$(echo "scale=3; $sum + $pow" | bc)
done
echo "Sum is : $sum"