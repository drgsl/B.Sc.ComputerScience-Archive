#!/bin/bash

if test $# -eq 0 ; then
  read -p "Introduceti username-ul dvs. de pe serverul fenrir: " username
else
  username=$1
fi

set -x

# informatii despre distributia de Linux instalata
hostnamectl status > distro_${username}_.txt


# informatii despre disc si file-system-ele montate
lsblk -f > disc_${username}_.txt


# La final, arhivam informatiile colectate, pentru pastrarea integritatii la upload
zip info_${username}_.zip  dis*_${username}_.txt
