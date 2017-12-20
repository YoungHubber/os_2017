#!/bin/bash
if [ $# -ne 1 ]
then
  exit 1
fi
filename="in.txt"
s=$1
num=0
p=$(awk -F ' ' '{print $1}' $filename)
for line in $p; do
	if [ $line = $s ]; then
		let num=num+1
	fi
done
echo "number:$num"