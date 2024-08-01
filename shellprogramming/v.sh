#!/bin/bash
nl=$'\n'
echo -e "4. PRINT PATTERN ${nl}  "

echo "The pattern is "

for (( i = 0; i < 4; i++ ))
do
   for (( j = 0; j <= i ; j++ ))
	do
	echo -n  "*"
	done
	echo " "
done
