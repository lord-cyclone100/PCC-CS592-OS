list=`cat prog5.txt`

for i in $list
do
    word=${i%%[;,.]}
    rev=$(echo $word | rev)
    if [ "$word" = "$rev" ]
    then
        echo "$word is a palindrome"
    fi
done