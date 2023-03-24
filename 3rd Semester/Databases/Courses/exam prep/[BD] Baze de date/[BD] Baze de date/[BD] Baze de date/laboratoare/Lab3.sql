--1.Write a query to display the current date. Label the column Date
SELECT SYSDATE AS "Date" 
from dual

--2.Display the employee's name, hire date and salary review date, which is the first Monday after six months of service. 
--Label the column REVIEW. Format the dates to appear in the format to "Sunday, the Seventh of September, 1981"
select ename,hiredate,to_char(next_day(ADD_MONTHS(hiredate,6),01),'day ,fmDdspth "of" MONTH , YYYY') review
from emp
order by hiredate

--3.For each employee display the employee name and calculate the number of months between today and the date the 
--employee was hired. Label the column MONTHS_WORKED. Order your results by the number of months employed. 
--Round the number of months up to the closest whole number.
select ename,trunc(months_between(sysdate,hiredate)) MONTHS_WORKED 
from emp
order by MONTHS_WORKED

--4.Write a query that produces the following for each employee:
--<employee name> earns <salary> monthly but wants <3 times salary>. Label the column Dream Salaries
select ename || ' earns ' || sal || ' monthly, but wants ' || sal*3 as Dream_Salaries
FROM EMP
order by sal

--5.Create a query to display name and salary for all employees. Format the salary to be 15 characters long, 
--left-padded with $. Label the column SALARY.
select ename,lpad(sal,15,'$') special_salary
from emp
order by sal

--6.Write a query that will display the employee’s name with the first letter capitalized and all
--other letters lowercase and the length of their name, for all employees whose name starts with
--J, A, or M. Give each column an appropriate label.
select initcap(ename)name,length(ename)name_length
from emp
where ename like 'M%' or ename like 'A%' or ename like 'J%'
order by ename
--
select initcap(ename)name,length(ename)name_length
from emp
where ename like upper('m%') or ename like 'A%' or ename like 'J%'
order by ename

--7.Display the name, hire date, and day of the week on which the employee started. Label
--the column DAY. Order the results by the day of the week starting with Monday.
select ename, to_char(hiredate,'DD/MM/YY') hiredate, to_char(hiredate,'day') day
FROM EMP
order by day

--8.Create a query that will display the employee name and commission amount. If the employee
--does not earn commission, put “No Commission”. Label the column COMM.
select ename,decode(comm,0,'no commission',null,'no commission',comm) comm
from emp
order by comm

--9.Afisati numele angajatilor si numele oraselor în care lucreaza interogând doar tabela EMP
select ename,loc
from emp natural join dept
where deptno is not null
order by loc
--sau
select ename,loc
from emp e inner join dept d on e.deptno=d.deptno
order by loc

--10.Afisati pentru angajatii care nu castiga comision numele, numarul de zile lucrate si jobul
select ename,lpad(round(sysdate-hiredate),7) Days_Worked,job
from emp
where comm is null
order by Days_Worked

--11.Afisati numele tuturor angajatilor înlocuind aparitia literei i cu y si aparitia literei y cu i
select ename, replace(ename,'i','y')name_changed
from emp
where ename like '%i%'
union
select ename, replace(ename,'y','i')name_changed
from emp
where ename like '%y%'


--12.Daca salariul angajatilor creste la implinirea a 32 ani vechime cu 10%, afisati numele fiecarui
--angajat, data angajarii, data la care are loc marirea salariului, numarul de luni de asteptare pana la marire 
--si valoarea noului salariu.
SELECT ENAME,HIREDATE,ADD_MONTHS(HIREDATE,384) DATA_MARIRE,
MONTHS_BETWEEN(ADD_MONTHS(HIREDATE,384),HIREDATE)NR_LUNI_ASTEPTARE,
LPAD(ROUND(SAL*1.1),7)SALARIU_MARIT
from emp
order by Data_Marire

--13.Presupunând ca salariul se mareste cu fiecare luna ce trece de la data angajarii cu 1%, iar
--salariul stocat în baza de date e cel primit la data angajarii, care a fost salariul fiecarui angajat pe
--data de 1 ianuarie anul 2000 (afisati numele angajatului si valoarea salariului)?
select ename, hiredate, lpad(sal,7) salary,round(months_between(to_date('01-FEB-2000'),hiredate)) Nr_luni,
lpad(round(sal+sal*round(months_between(to_date('01-FEB-2000'),hiredate))*0.01),7) sal_marit
from emp
order by ename

--14.Consideram ca salariul se mareste cu fiecare an de vechime cu 10%, pentru cei ce nu castiga
--comision si cu 5% pe an pentru cei ce beneficiaza de comision. Cat castiga fiecare angajat in
--luna curenta? Afisati numele cu majuscule si salariul cu 2 zecimale.
SELECT INITCAP(ENAME)NAME,LPAD(SAL,7)INITIAL_SALARY,LPAD(COMM,4)COMM,
lpad(round(months_between(sysdate,hiredate)/12),5) ani_de_munca,
lpad(round(sal*(1+round(months_between(sysdate,hiredate))/12*0.1)),7) sal_marit
from emp
where comm is null
union
SELECT INITCAP(ENAME)NAME,LPAD(SAL,7)INITIAL_SALARY,LPAD(COMM,4)COMM,
LPAD(ROUND(MONTHS_BETWEEN(SYSDATE,HIREDATE)/12),5) ani_de_munca, 
lpad(round(sal*(1+round(months_between(sysdate,hiredate))/12*0.05)),7) sal_marit
from emp
where comm is not null
order by sal_marit