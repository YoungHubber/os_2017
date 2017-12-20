#!/usr/bin/awk -f

#
# Average Value of All Integers in a File 
#

BEGIN {
  n = 0;
  sum=0
}

{
  for (i=1; i<=NF; i++) {
    sum = sum + $i
    n++;
  }
}

END {
  printf "Res = %f\n" , sum/n
}

