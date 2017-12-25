#!/usr/bin/awk -f
BEGIN {
  vowels="aeiou"
}
{
  for(i=1;i<=NF;i++) {
    if (length($i)==5) {
    	split($i,v,"");
    	found=0;
    	for(j=1;j<=5;j++) {
        if (match(vowels,v[j])>0)
          found++;
      }
      if (found>=2) {
        count[$i]++;
        if (count[$i] == 1) 
          words[$i]=$i;
      }
    }
  }
}
END {
  for(w in words) {
    printf "%s ", words[w];
    for (j=count[words[w]];j>=1;j--) {
      printf "#";
    }
  printf "\n";
  }
}
