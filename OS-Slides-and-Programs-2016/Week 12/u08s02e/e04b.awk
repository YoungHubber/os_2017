#!/usr/bin/awk -f

#
# Print list of word frequencies
# Version 2: Get Rid of Punctuation and Case Distinction
# run it as: file.awk | sort -nr
#

{
  $0 = tolower($0) # remove case distinctions
  gsub(/[^a-z0-9_ \t]/, "", $0) # remove punctuation
  for (i = 1; i <= NF; i++)
  freq[$i]++
}

END {
  for (word in freq)
  printf "%s\t%d\n", word, freq[word]
}


