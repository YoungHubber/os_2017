#!/bin/bash
if [ $# -ne 1 ]
then
  exit 1
fi
filename=$1
max=0
nlines=$(cat $filename | wc -l)
while read line; do
	nwords=$(echo $line | wc -w)
	if [ $nwords -gt $max ]; then
		max=$nwords
	fi
done < $filename
echo "max:$max"
echo "lines:$nlines"