checkPalindrome(){
    a=$nums
    num=$a
    rev=0
    while [ $a -ne 0 ]
    do
        rem=$((a%10))
        rev=$((rev*10+rem))
        a=$((a/10))
    done
    if [ $rev -eq $num ]
    then
        echo "$num is a palindrome"
    else
        echo "$num is not a palindrome number"
    fi
}

lines=`wc -l < prog27.txt`
for i in $(seq $((lines+1)))
do
    nums=`head -n $i prog27.txt | tail -n 1 `
    (checkPalindrome $nums)
done