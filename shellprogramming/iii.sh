#!/bin/bash

nl=$'\n'
echo -e "3. COUNT OCCURENCE OF A PARTICULAR CHARACTER IN AN INPUT STRING ${nl}  "

echo -n "Enter a string: "
read string1

echo -n "Enter the character whose occurence you want to find: "
read c

count=$(echo "$string1" | grep -o "$c" | wc -l)

echo "The number of occurence of '$c' in '$string1' : $count "