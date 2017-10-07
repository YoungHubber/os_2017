BEGIN {
  lineCount=0;
}

{
  lineCount++;
  line[lineCount]=$0 ;
  nw[lineCount]=NF;
}

END { 
  for (i=1; i<=lineCount; i++)
    print nw[i], lineCount, line[i]
}

