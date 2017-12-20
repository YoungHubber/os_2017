#!/usr/bin/awk -f
BEGIN {
  fileO = ARGV[3];
  delete ARGV[3];
  printf "" > fileO
# File 1 - Amount
  while ((getline < ARGV[1])) {
    q[$1] = q[$1] + $2;
    n[$1]++;
  }
# File 2 - Price
  while ((getline < ARGV[2])) {
    p[$1] = p[$1] + $2;
  }

}
END {
  for (i in q) {
    if (i in p) {
     p[i] = p[i] / n[i];
      print i " " q[i] " " p[i] " " q[i]*p[i];
      print i " " q[i] " " p[i] " " q[i]*p[i] >> fileO
    }
  }
  
  for (i in p) {
    if ( !(i in q) ){
      print "Warning: product " i " has no amount!"
    }
  }

  for (i in q) {
    if ( !(i in p) ) {
      print "Warning: product " i " has no price!"
    }
  }  
}
