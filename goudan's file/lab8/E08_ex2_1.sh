#!/bin/bash
orgfile="in.txt"
sortfile_p="in_sorted_p.txt"
awk 'NR>1' $orgfile | sort -n -k 1 $orgfile >$sortfile_p