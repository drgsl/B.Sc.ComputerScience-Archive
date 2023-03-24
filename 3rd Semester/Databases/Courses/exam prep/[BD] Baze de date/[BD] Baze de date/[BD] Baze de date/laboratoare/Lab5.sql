--Exemplu
select dname,loc,count(empno)Nr_Ang,lpad(round(avg(sal)),7)Sal_Mediu
from dept d inner join emp e on e.deptno=d.deptno 
group by dname,loc
order by dname

--1.Display the highest, lowest, sum, and average salary of all employees. Label the columns
--Maximum, Minimum, Sum, and Average, respectively. Round your results to the decimal
--position
select max(sal) Maximum,min(sal)Minimum,sum(sal)Sum,round(avg(sal),2)Average
from emp

--2.Display the minimum, maximum, sum, and average salary for each job type
select job, lpad(max(sal),7)Maxim,lpad(min(sal),7)Minim,lpad(sum(sal),7)Suma,lpad(round(avg(sal)),7)Media
from emp
group by job
order by job

--3.Write a query to display the number of people with the same job
select job,count(*)No_of_people_with_same_job
from emp
group by job
order by job
--varianta interactiva
select job,count(*)No_of_people_with_same_job
from emp
where job='&job'
group by job
order by job

--4.Determine the number of managers without listing them. Label the column Number of Managers
select count(distinct mgr) Number_of_Managers
from emp

--5.Write a query that will display the difference between the highest and lowest salaries. Label the column Difference
select max(sal)-min(sal) Difference
from emp

--6.Display the manager number and the salary of the lowest paid employee for that manager.
--Exclude anyone where the manager id is not known. Exclude any groups where the minimum
--salary is less than $1000. Sort the output in descending order of salary.
--clauza where nu poate fi folosita pentru a restrictiona date ce intra in componenta grupurilor
--nu folositi clauza where pentru restrictionarea grupurilor, ci clauza having !
--nu folositi functii de grup in clauza where
select e.mgr,lpad(min(e.sal),7)Minimum_Salary
from emp e inner join emp m on e.mgr=m.empno 
group by e.mgr
having min(e.sal)>1000
minus
select e.mgr,lpad(min(e.sal),7)
from emp e inner join emp m on e.mgr=m.empno 
where e.mgr is null
group by e.mgr
--sau
select e.mgr,lpad(min(e.sal),7)Minimum_Salary
from emp e inner join emp m on e.mgr=m.empno 
where e.mgr is not null
group by e.mgr
having min(e.sal)>1000
order by min(e.sal)desc
--
select mgr,lpad(min(sal),7)Minimum_Salary
from emp
where mgr is not null
group by mgr
having min(sal)>1000
order by min(sal)desc

--7.Write a query to display the department name, location name, number of employees, and the
--average salary for all employees in that department. Label the columns dname, loc,
--Number of People, and Salary, respectively.
select dname,loc,count(*)Number_of_People,lpad(round(avg(sal)),7) Salary
from emp e inner join dept d on e.deptno=d.deptno
group by dname,loc
order by dname

--8.Create a query that will display the total number of employees and of that total the number
--who were hired in 1980, 1981, 1982, and 1983
select 'Total' An, count(empno) Nr_of_Emp from emp;
(select 1980 An, count(empno) Nr_of_Emp from emp where hiredate between '01/01/1980' and '31/12/1980');
(select 1981 An, count(empno) Nr_of_Emp from emp where hiredate between '01/01/1981' and '31/12/1981'); 
(select 1982 An, count(empno) Nr_of_Emp from emp where hiredate between '01/01/1982' and '31/12/1982'); 
(select 1983 An, count(empno) Nr_of_Emp from emp where hiredate between '01/01/1983' and '31/12/1983'); 
--sau
--functia decode evalueaza o expresie intr-un mod similar structurii if-then-else
--evalueaza expresia dupa ce o compara cu fiecare valoare cautata
--daca valoarea expresiei este identica cu valoarea continuta in cautare atunci este intoarsa expresia result
select count(*) total,
sum(decode(to_char(hiredate, 'YYYY'),1980,1,0))"1980",
sum(decode(to_char(hiredate, 'YYYY'),1981,1,0))"1981",
sum(decode(to_char(hiredate, 'YYYY'),1982,1,0))"1982",
sum(decode(to_char(hiredate, 'YYYY'),1983,1,0))"1983"
from emp;

--9.Create a matrix query to display the job, the salary for that job based upon department number
--and the total salary for that job for all departments, giving each column an appropriate label
select job,sum(decode(deptno,10,sal))dept10,sum(decode(deptno,20,sal))dept20,sum(decode(deptno,30,sal))dept30,sum(sal)total
from emp
group by job

--Probleme suplimentare
--1.Sa se afiseze numarul departamentului si salariul maxim pentru pentru acele departamente la care salariul maxim este mai 
--mare de 2500
--mai intai se gaseste salariul maxim pentru fiecare departament grupand dupa numarul departamentului
--apoi, are loc restrictionarea grupurilor la acele departamente ce au salariu maxim mai mare de 2500
select deptno,max(sal)Sal_Max
from emp
group by deptno
having max(sal)>2500
order by deptno

--2.Sa se afiseze numerele departamentelor si salariul mediu la acele departamente la care salariul maxim este mai mare de 2500
select deptno,round(avg(sal))Sal_Mediu
from emp
group by deptno
having max(sal)>2500
order by deptno

--3.Sa se afiseze salariul mediu maxim, adica valoarea maxima a salariului mediu
select round(max(avg(sal)))Val_Max_Sal_Mediu
from emp 
group by deptno

--4.Afisati meseria, nr departmamentului, suma salariilor pentru meseria respectiva din cadrul departamentelor 10 si 20 precum si
--salariul total pentru acea meserie pentru toate departamentele luate in considerare.
--operatorul cube este folosit in rapoarte de tip cross-tab
--produce rezultate pentru toate combinatiile posibile specificate in group by, precum si un total general
select job, deptno, lpad(sum(sal),7)Sum_of_Salary 
from emp
where deptno in (10,20)
group by cube(deptno,job)
order by job,deptno
--
select job, deptno, lpad(sum(sal),7)Sum_of_Salary 
from emp
where deptno in (10,20)
group by rollup(deptno,job)
order by job,deptno

--5.Scrieti o interogare care sa afiseze urmatoarele informatii referitoare la angajati:
--marca managerului, jobul si salariul total pentru fiecare job pentru angajatii care au acelasi sef, salariul total pe care sefii
--trebuie sa il plateasca angajatilor, salariul total pe care sefii trebuie sa il plateasca angajatilor, indiferent de job
--operatorul rollup se foloseste pentru a obtine rezultate cumulative, precum subtotaluri si trebuie specificat in clauza group by
--gruparea cu rollup duce la obtinerea unui set de rezultate ce contine pe langa valorile pentru randurile grupate in mod obisnuit si valorile
--pentru subtotal
select mgr,job,lpad(sum(sal),7) Salariu, lpad(count(job),6) Nr_Joburi 
from emp
group by rollup(mgr,job)
order by mgr

--6.Sa se calculeze suma pentru urmatoarele grupuri:(deptno,job,mgr),(deptno,mgr)
--si (job,mgr)
--grouping sets permite specificarea unei grupari multiple a datelor 
--se calculeaza toate gruparile specificate in clauza grouping sets si se combina rezultatele grupurilor individuale cu o operatie
--de tip union all
select deptno,job,mgr,lpad(round(avg(sal)),10) Salariu
from emp
group by grouping sets((deptno,job,mgr),(deptno,mgr),(job,mgr))
order by deptno
--
select deptno,job,mgr,lpad(round(avg(sal)),10) Salariu
from emp
group by grouping sets(deptno,job,mgr)
order by deptno,job,mgr

--7.Sa se afiseze cu ajutorul operatorului cube numarul departamentului, numele functiei, marca managerilor si salariul mediu
--al acestora
select deptno,job,mgr,lpad(round(avg(sal)),10) Salariu_Mediu
from emp
group by cube(deptno,job,mgr)
order by deptno

--8.Sa se calculeze salariul total pentru fiecare functie din departament
--interogarea afiseaza urmatoarele grupuri:
--(deptno,job,mgr),(deptno,job),(deptno) si (deptno,mgr)
select deptno,job,mgr,sum(sal)Sal_Total
from emp
group by deptno,rollup(job),cube(mgr)
order by deptno
