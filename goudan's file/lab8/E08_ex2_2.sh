#!/bin/bash
orgfile="in.txt"
sortfile_q="in_sorted_q.txt"
awk 'NR>1' $orgfile | sort -n -k 2 $orgfile >$sortfile_q