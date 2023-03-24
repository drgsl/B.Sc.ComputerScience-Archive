/*Subiectul 1
========================
Sa se afiseze numele angajatilor,salariul actual,data de angajare 
pentru acei angajati care au venit in firma
dupa jumatatea anului de angajare si au functia Clerk.*/
select ename,sal,hiredate
from emp 
where job='clerk' and to_char(hiredate,'mm')>6

/*Subiectul 2 
========================
Afisati salariatii care s-au angajat in firma dupa managerii lor (adica au data de angajare mai mare), doar pentru managerii care au 
gradul 4. Veti afisa urmatoarele informatii nume angajat, data angajare subordonat, 
nume manager, data angajare manager folosind alias-uri semnificative. 
Ordonati afisarea dupa data de angajare a managerilor.*/


/*Subiectul 3
========================
Modificati comisionul managerilor de departamente(mgr din emp) astfel incit sa fie egal cu cel al unui reprezentant de vinzari 
(cei cu job=salesman) dat ca parametru (ename).
Reveniti la datele initiale.*/

  
/*Subiectul 4 
========================
Afisati toti angajatii, data angajarii si salariul pentru cei care au venit in firma inainte 
de anul 1982 si au functia 'salesman'*/
select ename,hiredate,lpad(sal,7)sal
from emp
where to_char(hiredate,'yyyy')<1982 and job='salesman'
order by sal

/*Subiectul 5
========================
Afisati numele departamentelor si suma salariilor pe departamente pentru acelea
a caror suma salariala este mai mare decit cel mai mare salariu care poate fi obtinut
in firma*/


/*Subiectul 6 
========================
Folosind clauza WITH sa se afiseze numele departamentelor a caror valoare minima a datei de 
angajare este mai mare decit aceeasi valoare din locatiile (campul loc din tabela dept)
in care se afla aceste departamente.*/

with
dept_ang as
(select dname,min(hiredate) min_dept
from emp e inner join dept d on e.deptno=d.deptno
group by dname),
loc_ang as
(select loc,min(hiredate) min_loc
from emp e inner join dept d on e.deptno=d.deptno
group by loc)
select da.dname,min_dept,min_loc
from dept_ang da inner join dept d on d.dname=da.dname inner join loc_ang l on l.loc=d.loc
where min_dept>min_loc

