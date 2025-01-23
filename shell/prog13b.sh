updateRecord(){
    echo "Enter name of student to update marks : "
    read name
    echo "Enter new marks : "
    read marks
    lines=`wc -l < prog13b.txt`
    for i in $(seq 1 $lines)
    do
        r=`head -n $i prog13b.txt | tail -n 1 | cut -d "|" -f1`
        n=`head -n $i prog13b.txt | tail -n 1 | cut -d "|" -f2`
        m=`head -n $i prog13b.txt | tail -n 1 | cut -d "|" -f3`
        if [ "$n" = "$name" ]
        then
            echo "$r|$n|$marks" >> prog13b1.txt
        else
            echo "$r|$n|$m" >> prog13b1.txt
        fi
    done

    mv prog13b1.txt prog13b.txt
}

(updateRecord)