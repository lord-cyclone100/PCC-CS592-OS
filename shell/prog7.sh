for i in "$@"
do
    echo "$i"
    characters=`wc -m $i | cut -d " " -f1`
    words=`wc -w $i | cut -d " " -f1`
    lines=`wc -l $i | cut -d " " -f1`
    echo "Number of characters : $characters"
    echo "Number of words : $words"
    echo "Number of lines : $((lines+1))"
    echo "------------------------"
done