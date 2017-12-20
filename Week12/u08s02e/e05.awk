#!/usr/bin/awk -f

#
# Matrix Transpose
#

{
  if (maxNC < NF)
    maxNC = NF
  maxNR = NR
  for (i=1; i<=NF; i++)
      matrix[NR, i] = $i
}

END {
  for (c=1; c<=maxNC; c++) {
    for (r=1; r<=maxNR; r++)
      printf("%s ", matrix[r, c])
   printf("\n")
  }
}


