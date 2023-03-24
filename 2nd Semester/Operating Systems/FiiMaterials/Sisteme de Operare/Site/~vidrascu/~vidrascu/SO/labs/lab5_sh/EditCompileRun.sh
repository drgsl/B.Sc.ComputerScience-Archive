#!/bin/bash
### EditCompileRun.sh : Script pentru automatizarea procesului de dezvoltare de programe C ###

if [ $# -eq 0 ]
then
    read -p "Dati numele fisierului sursa .c : " fisier
else
    fisier=$1
fi

while true
do
    mcedit $fisier     # se va inlocui comanda mcedit cu numele editorului preferat (e.g., nano, vim, etc. sau GUI editors: gedit, kedit, etc.)

    read -p "Doriti compilarea programului? (y/n) " answer
    if [ $answer = "y" ]
    then
        output=$(dirname $fisier)/$(basename $fisier .c).exe
            # Sau: putem omite sufixul .exe ; Extensia .exe nu este obligatorie, d.p.d.v. al SO-ului Linux !

        gcc $fisier -o $output -Wall  # compilare
        if [ $? -eq 0 ]               # s-a compilat fara erori?
        then
            read -p "Doriti executarea programului? (y/n) " answer
            if [ $answer = "y" ]
            then
                ./$output
            fi
            break
        else                          # au fost erori la compilare
            read -p "Apasa <Enter> pentru a continua cu editarea erorilor..." answer   # acest read are doar rol de pauza
            continue
        fi
    else
        break
    fi
done

exit 0  # Succes!
