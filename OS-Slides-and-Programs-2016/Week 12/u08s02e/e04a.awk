#!/usr/bin/awk -f

#
# Print list of word frequencies
#

{
  for (i = 1; i <= NF; i++)
  freq[$i]++
}

END {
  for (word in freq)
  printf "%s\t%d\n", word, freq[word]
}


