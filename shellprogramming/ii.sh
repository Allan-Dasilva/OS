nl=$'\n'
echo -e "2. CHECK IF NUMBER IS PALINDROME OR NOT ${nl}  "



echo -n "Enter a number: "
read string

num=$((string))

rev=$(echo $num | rev )

echo $nl
if [ $num == $rev ]
then
echo "The number '$num' is a palindrome"

else
echo "The number '$num' is not a palindrome"
fi


