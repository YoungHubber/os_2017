#!/bin/bash
orgfile="in.txt"
outfile="out.txt"
cat $orgfile | awk -F " " '{print $1}' | sort | uniq | tr '[a-z]' '[A-Z]' > $outfile