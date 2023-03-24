/*Subiectul nr. 1
========================
Sa se preia de la tastatura numele unui manager. Sa se modifice salariile tuturor 
subordonatilor lui adaugind la salariul existent a 100-a parte din SALARIUL MAXIM 
aferent functiei managerului.
Afisati coloanele semnificative ptr. inregistrarile modificate (DOAR ACESTEA !!). 
Reveniti la datele initiale. Afisati si acum pentru verificare.*/


/*Subiectul 2 
========================
Afisati salariatii care s-au angajat in firma dupa managerii lor, doar pentru managerii care au 
gradul 4. Veti afisa urmatoarele informatii nume angajat, data angajare subordonat, 
nume manager, data angajare manager folosind alias-uri semnificative. 
Ordonati afisarea dupa data de angajare a managerilor.*/
select e.ename Subordonat,e.hiredate Data_Subordonat,m.ename Manager,m.hiredate Data_Manager
from emp e inner join emp m on e.mgr=m.empno inner join salgrade s on e.sal between losal and hisal
where grade=4 and e.hiredate>m.hiredate
order by m.hiredate

/*Subiectul 3
========================
Modificati comisionul managerilor de departamente(campul mgr din tabela emp) astfel incit sa fie egal cu cel al unui reprezentant de vinzari 
(i.e cei cu job = salesman) dat ca parametru (ename), pentru acei manageri 
care lucreaza in New York (campul loc din tabela dept).
Afisati coloanele semnificative ptr. inregistrarile modificate (DOAR ACESTEA !!). 
Reveniti la datele initiale. Afisati si acum pentru verificare.*/


/*Subiectul 4
Afisati numele departamentului (din tabela dept) si numarul de angajati din cadrul 
acestuia pentru fiecare departament care are o medie salariala de peste 2500.
Denumiti coloana aferenta numarului de angajati: "nr angajati".*/



  




