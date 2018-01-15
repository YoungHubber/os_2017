#!/bin/bash
if [ $# -ne 1 ]
then
  exit 1
fi
filename=$1
totlines=0
while read line; do
	subfile=$line
	if [ -f $subfile ]; then
		if [ -r $subfile ]; then
			size=$(wc -c $subfile | awk '{print $1}')
			if [[ $size -gt 1024 ]]; then
				sublines=$(cat $filename | wc -l)
				echo $subfile
				let totlines=totlines+sublines
			fi
		fi
	elif [ -d $subfile ]; then
		echo $subfile
		for file in subfile
		do
			subfile=$line
			if [ -f $subfile ]; then
				if [ -r $subfile ]; then
					size=$(wc -c $subfile | awk '{print $1}')
					if [[ $size -gt 1024 ]]; then
						sublines=$(cat $filename | wc -l)
						echo $subfile
						let totlines=totlines+sublines
					fi
				fi
			fi
		done
	fi
done < $filename
echo "total: "$totlines" lines"