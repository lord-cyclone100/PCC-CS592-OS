ls ./prog9 > prog9.txt
c=`ls -p ./prog9 | grep -v / | wc -l` #grep -v / means exclude all ending with '/' i.e. directories
echo "There are $c files" >> prog9.txt