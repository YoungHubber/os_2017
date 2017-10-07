#!/bin/sh

# Set directory
# dir="/usr/pap"
dir="."

# Solution 1
# N.B. "grep -v" == invert-match
for f in `find . -name "*.o" | grep -v "protetta"`
do
  echo "--> Command: rm $f"
  rm $f
done

for f in `find . -name "*.cpp" | grep -v "protetta"`
do
  echo "--> Command: rm $f"
  rm $f
done

# Solution 2
#rm `find $dir -name "*.cpp" -print | grep -v "protetta"`
#rm `find $dir -name "*.o" -print | grep -v "protetta"`