#!/bin/bash

if [ $# -eq 0 ]
then
    echo "Eroare: parametri insuficienti! Nu ati specificat numele directorului."
    exit 1  # Fail!
fi

if [ ! -d $1 -o ! -r $1  ]
then
    echo "Eroare: $1 nu este director, sau nu aveti drept de citire a acestuia!"
    exit 2  # Fail!
fi

for sursa in $(find $1 -maxdepth 1 -name "*.cpp")
do
    baza=`basename $sursa .cpp`   # Extragem doar numele de bază al fișierului, fără calea până la el și fără sufixul .cpp
    dirn=`dirname $sursa`         # Luăm prefixul din numele fișierului, i.e. calea până la el; Nu va fi niciodată cuvântul vid, ci va fi cel puțin '.'
    executabil=$dirn"/"$baza      # Construim noul nume, cu tot cu calea până la el!

    echo "Compilam fisierul $sursa si obtinem executabilul $executabil (doar dacă nu vor fi erori la compilare...)"
    g++ $sursa -o $executabil -Wall
done

exit 0  # Succes!
