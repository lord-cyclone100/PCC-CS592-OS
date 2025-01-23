checkPalindrome(){
    a=$1
    num=$a;
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
        echo "$num is not a palindrome"
    fi
}

for i in "$@"
do
    (checkPalindrome $i)
done