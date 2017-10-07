#!/bin/bash

#dir = "~"
dir="."

# per ogni file (-type f) trovato di nome *.txt
for f in `find $md -type f -name "*.txt"`
do

#estraggo il nome dal path name
name=`basename $f ".txt"`

#copio i nomi in un file temporaneo
echo $name >> tmpFile.txt

done

# elenco la lista dei nomi, la ordino e con uniq elimino i doppioni
cat tmpFile.txt | sort | uniq

rm -rf tmpFile.txt

