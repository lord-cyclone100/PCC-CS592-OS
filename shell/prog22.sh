cd ./prog22

for i in "$@"
do
    if [ -d "$i" ]
    then
        echo "$i is a directory"
        echo "------------------"
    else
        echo "$i is a file"
        lines=`wc -l < "$i"`
        words=`wc -w < "$i"`
        echo "$i has $((lines+1)) lines and $((words+1)) words"

        if [ ! -w "$i" ]
        then
            echo "$i does not have write access"
            echo "giving write access"
            chmod g+w "$i"
            echo "write access given"
        else
            echo "$i has write access"
            echo "removing write access"
            chmod g-w "$i"
            echo "write access removed"
        fi
        echo "------------------"
    fi
done