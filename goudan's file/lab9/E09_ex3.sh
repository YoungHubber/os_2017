#!/bin/bash
if [ $# -ne 3 ]
then
  exit 1
fi
user=$1
gid=$2
name="$3"
olduid=$(cat /etc/passwd | tail -n 1 $filename | cut -d ':' -f 4)
let uid=olduid+1
echo $uid
append=$user":x:"$gid":"$uid":""$name"",,,:/home/"$user":/bin/bash"
echo $append
echo append >> /etc/passwd