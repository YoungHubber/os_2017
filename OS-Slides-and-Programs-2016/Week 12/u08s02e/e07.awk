#!/usr/bin/awk -f

#
# Associative arrays
#

{
  voc[$1]=$2;
}

END {
  for (i in voc)
    printf ("%s --> %s\n", i, voc[i]);
}



