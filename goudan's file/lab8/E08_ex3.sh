#!/bin/bash
if [ $# -ne 2 ]
then
  exit 1
fi
filename=$1
ex=$2
while read line ; do
	a=1
	b=1
	sum=0
	i=3
	newname=$ex$line.$ex
	if [ $line -eq 1 ] ; then
		echo "$a " >>$newname
	elif [ $line -eq 2 ] ; then
		echo "$a $b " >>$newname
	else
		echo -e "$a $b \c" >>$newname
		while [ $i -le $line ] ; do
        	let sum=$a+$b
        	let b=$a
        	let a=$sum
       	 	echo -e "$sum \c"
       	 	let i=$i+1
        done >>$newname
        echo -e "\n" >>$newname
    fi
done < $filename