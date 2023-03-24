#!/bin/bash
### Afișează lista parametrilor cu care este apelat. ###

echo "Suntem in scriptul my_script.sh !"

echo "Acesta a fost apelat cu numele \$0=$0 si cu parametrii urmatori:"
i=0
for parametru in $@
do
  let i=i+1
  echo "param_$i = $parametru"
done

echo "Folosind comanda ps -f in script, putem vedea ce linie de comanda a 'construit' apelul execv pentru a rula acest script:"
ps -f
