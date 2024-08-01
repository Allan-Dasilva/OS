#!/bin/bash
nl=$'\n'
echo -e "1. SORT NUMBER IN ASCENDING ORDER ${nl}  "

echo -n "Enter the number of elements: "
read n

echo "Enter elements"
for (( i=0; $i < $n ; i=$i+1 ))
do
echo -n "Enter $(($i+1)): "
read x
echo "$x">>a.txt
done

echo "sorted elements are: "


sort a.txt

#clears the file..
echo -n>a.txt

