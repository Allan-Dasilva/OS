
#!/bin/bash

nl=$'\n'
echo -e "4. FIND THE SMALLEST DIGIT OF A NUMBER ${nl}  "


smallest=10

echo -n "Enter a number: "
read n
num=$n

while [ $num -ne 0 ]
do
rem=$(( num % 10 ))

if [ $rem -lt $smallest ]
then
        smallest=$rem
fi
num=$(( num / 10 ))
done


echo "The smallest digit of $n is $smallest"