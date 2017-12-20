#!/usr/bin/awk -f

#
# Translation: Get Vocabulary From file e06in1.txt
#

BEGIN {
  while (getline < "u11s03e06.in1"){
    voc[$1]=$2;
  }
}

{
  for(i=1; i<=NF; i++){
    if ($i in voc) {
      printf ("%s --> %s\n", $i, voc[$i]);
    } else {
      printf ("%s --> ?\n", $i);
    }
  }
}



