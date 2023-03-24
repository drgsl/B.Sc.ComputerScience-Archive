#!/bin/bash

function compilare()
{
    output=$(dirname $1)/$(basename $1 .c).exe
    gcc $1 -o $output -Wall
}

function afisare()
{
    echo "Continutul fisierului $1 este:"
    cat $1
}

# Validarea datelor de intrare

if [ $# -eq 0 ]
then
    echo "Utilizare: $0 director"
    exit 1  # Fail!
fi

if [ ! -d $1 -o ! -r $1  ]
then
    echo "Eroare: Primul argument, $1, nu este director, sau nu aveti drept de citire a acestuia!"
    exit 2  # Fail!
fi

for f in $(ls -A $1)
do
    case $1/$f in
      *.c   ) echo "fisier sursa C: $f" ; compilare $1/$f ;;
      *.txt ) echo "fisier text: $f"    ; afisare $1/$f ;;
    esac
done

exit 0  # Succes!
