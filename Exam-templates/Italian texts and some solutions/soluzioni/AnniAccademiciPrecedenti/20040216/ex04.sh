#!/bin/bash

cont="0"
val1="0"
val2="0"
val3="0"

while true; do
  cont=$[$cont+1]

  echo -n "Value: ";
  read val1;

  if [ $cont -ge 3 -a $val1 -eq $val2 -a $val2 -eq $val3 ]; then
    echo "Uguali!"
    break
  else
    val3=$val2
    val2=$val1
  fi
done

exit 0
