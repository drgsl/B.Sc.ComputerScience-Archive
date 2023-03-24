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

for sursa in $1/*.cpp
do
    executabil=$1/$(basename $sursa .cpp).exe     # Construim noul nume, cu tot cu calea până la el!
        # Sau: putem omite sufixul .exe ; Extensia .exe nu este obligatorie, d.p.d.v. al SO-ului Linux !

    echo "Compilam fisierul $sursa si obtinem executabilul $executabil, in acelasi director cu sursa (doar dacă nu vor fi erori la compilare...)"
    g++ $sursa -o $executabil -Wall
done

exit 0  # Succes!
