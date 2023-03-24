#!/bin/bash
### Running a SPMD program. ###


# Validarea datelor de intrare

if [ $# -eq 0 ]
then
    read -p "Dati calea catre programul/scriptul pe care doriti sa-l executati in maniera SPMD: " spmd
else
    spmd=$1
fi

if [ ! -f $spmd -o ! -x $spmd ]
then
    echo "Eroare: nu exista fisierul/calea $spmd (sau nu aveti drept de executie asupra lui) !"
    exit 1  # Fail!
fi

shift

if [ $# -eq 0 ]
then
    read -p "Dati numarul de instante dorit pentru executia programului SPMD: " n
else
    n=$1
fi

if [ ! $n -gt 0 ]
then
    echo "Eroare: numarul de instante trebuie sa fie minim 1 !"
    exit 2  # Fail!
fi

shift

declare -a val   # declara val ca fiind un array

for i in $(seq 1 $n)
do
    if [ $# -eq 0 ]
	then
	    read -p "Dati argumentul val[$i]: " val[$i]
	else
	    val[$i]=$1
	    shift
	fi
done


# Lansarea în execuție paralelă și neînlănțuită a celor $n instanțe ale programului $spmd

for i in $(seq 1 $n)
do
    $spmd ${val[$i]} &
done

echo "Parallel SPMD job started!"

wait   # Astfel așteptăm terminarea execuției tuturor celor $n instanțe ale programului $spmd

echo "Parallel SPMD job finished!"
