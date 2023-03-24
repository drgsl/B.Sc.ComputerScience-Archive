#!/bin/bash

mkdir lab9_p1tmp

echo "Elementele de intrare:"
while read proc
do
    if ( echo $proc | grep "^[0-9]\{1,\}-[0-9]\{1,\}$" )
    then
	mkdir lab9_p1tmp/$proc
    else
	echo "Intrare incorecta : $proc"
    fi
done

echo -e "\nIerahia de procese este:"
change=0
until [ $change -eq 1 ]
do
    for proc in lab9_p1tmp/*
    do
	ppid=$( echo $proc | cut -d- -f2 )
	pdir=$( find lab9_p1tmp -name "$ppid-*" )
	if [ "$pdir" != "" ]
        then
	    mv $proc $pdir
	    change=1
	fi
    done
done

for proc in $( find lab9_p1tmp/* )
do
    for secv in $( echo $proc | tr / " " | cut -d" " -f3- )
    do
	echo -n "   |"
    done
    echo -n "   |-"
    basename $proc | cut -d- -f1
done

rm -r lab9_p1tmp
