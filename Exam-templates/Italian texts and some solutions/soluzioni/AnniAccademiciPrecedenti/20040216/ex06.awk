#!/usr/bin/awk -f

BEGIN {
  n = 0;
  sum = 0
}

{
  if ($1 ~ "WRD") {
    split ($3, vet, ",");
    if (length(vet[5])==1 && vet[5]!="@") {
#   if (vet[5]=="r" || vet[5]=="i" || vet[5]=="s" || vet[5]=="o") {
#     print " -> " $2 " ->" $3 "->" vet[1]-$2;
      n++;
      sum = sum + (vet[1] - $2);
    }
  }
}

END {

  printf "#Fonemi totali   = %d\n" , n;
  printf "Somma tempi      = %d\n" , sum;
  printf "Durata media [s] = %f\n" , sum/(100*n);
  printf "#Fonemi/sec      = %f\n" , (n*100)/sum;
}

