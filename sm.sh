# Name: Nick Avalani
# Course: CSc 352, Fall 2022, Benjamin Dicken
# File: sm.sh
# Description: This bash script searches the man page
#              of commands for a specific word/pattern.
#              The command with the highest occurence of
#              the word/pattern will be printed along 
#              with the number of matches.
#              The word/pattern and the commands are provided
#              in the command line.

#!/bin/bash

#Program to search for a term in the man pages

word=${1}

counts=()
commands=()
for cmd in ${@:2};                    #This loop finds the number of occurences in each command
do
	count=$(man ${cmd} | grep -o -i ${word} | wc -l)
	counts+=(${count})
	commands+=(${cmd})
done

index=0
i=0
max=${counts[0]}
for count in ${counts[@]};             #Loop to find maximum count
do
	if((${count} >= ${max}));then
		max=${count}
		i=${index}
		index=$((index+1)) 
	else
		index=$((index+1))
	fi
done

echo "Best match: ${commands[${i}]}"
echo "(term appeared ${max} times)"
