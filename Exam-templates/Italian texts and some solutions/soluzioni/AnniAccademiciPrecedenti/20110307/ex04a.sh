#!/bin/bash

#dir = "~"
dir="."

# per ogni file (-type f) trovato di nome *.txt
for f in `find $md -type f -name "*.txt"`
do

#copio i nomi in un file temporaneo
echo $f >> tmpFile1.txt

done

# sostituisco path ed estensione con nulla
sed 's#.*/\(.*\)\.txt#\1#g' tmpFile1.txt > tmpFile2.txt

#elenco la lista dei nomi, la ordino e con uniq elimino i doppioni
cat tmpFile2.txt | sort | uniq

rm -rf tmpFile1.txt
rm -rf tmpFile2.txt

