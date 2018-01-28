#!/bin/bash
if [ $# -ne 2 ]
then
  exit 1
fi
filename=$1
ch=$2
if [ $ch -eq 1 ]; then
	sort -k1nr $filename
elif [ $ch -eq 2 ] ; then
	sort -k2 $filename
elif [ $ch -eq 3 ] ; then
	awk '$NF ~ /2011\/2012/ {print $1}' $filename
elif [ $ch -eq 4 ] ; then
	awk '{for(i=3;i<=NF;i++)if($i~/INF1T3/)print $1,$i}' data.txt | sort
elif [ $ch -eq 5 ] ; then
	cat $filename | grep -E '^\w*[4,2] '| sort -k 2
elif [ $ch -eq 6 ] ; then
	awk '$NF ~ /attended/ && $(NF-1) ~ /yet/ && $(NF-2) ~ /Not/  {print $1}' $filename|sort
elif [ $ch -eq 7 ] ; then
	cat $filename | grep -E '^\w* \w*A\w\wA\w*'
elif [ $ch -eq 8 ] ; then
	cat $filename | grep -E '^\w* \w+A\w\wA\w+'
elif [ $ch -eq 9 ] ; then
	awk '{print $1}' data.txt |sed 's/0//g'|sed 's/8/1/g'|sort -n|uniq
elif [ $ch -eq 10 ] ; then
	awk '{print $1}' data.txt |sed 's/0//g'|sed 's/8/1/g'|sort -n|uniq -c|awk '{if($1 > 1){print $2,$1;}}' 
fi
