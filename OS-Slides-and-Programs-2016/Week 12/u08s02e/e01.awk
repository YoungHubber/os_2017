#!/usr/bin/awk -f

#
# Center file lines
#

BEGIN {
  # Line size
  SIZE = 80
}

{
  l = length($0);
  for (i=0; i<(SIZE-l)/2; i++)
    printf " ";
  printf "%s", $0;
  for (i=0; i<(SIZE-l)/2; i++)
    printf " ";
  printf "\n";
}

