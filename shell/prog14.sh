read -p "Enter the value of x : " x
read -p "Enter the value of n : " n

case $n in

1)
    pow=$(echo "$x"^2 | bc)
    y=$((1+pow))
;;
2)
    div=$(echo "scale=2; $x/$n" | bc)
    y=$(echo "scale=2; 1 + $div" | bc)
;;
3)
    y=$((1+(2*$x)))
;;
*)
    y=$((1+($n*$x)))
;;
esac

echo $y