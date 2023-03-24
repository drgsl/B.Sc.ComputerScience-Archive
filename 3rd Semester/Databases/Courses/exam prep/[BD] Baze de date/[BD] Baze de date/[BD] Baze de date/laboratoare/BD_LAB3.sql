Setul 1

1.SELECT sysdate "Date" from sys.dual;
//dual - pt a rula noi interogari pt care avem nevoie de un sg rez
-->ca o tabela care ne permite sa exec anumite functii
//sysdate as date from EMP -- se apeleaza pt fiecare linie din emp

2.SELECT ename, hiredate, to_char(next_day(add_months(hiredate,6), 'MONDAY'), 'DAY "the" Ddspth "of" MONTH, YYYY ') AS "REVIEW"
FROM emp;

DAY- ZIUA SAPTAMANII IN CARACTERE

3.SELECT ename, Round(months_between(sysdate, hiredate),0) AS "Months worked" 
FROM emp
ORDER BY "Months worked";

4. SELECT ENAME || ' earns ' || sal || ' monthly but wants ' || sal*3 "DREAM SALARIES"
FROM emp;

5.SELECT ENAME,LPAD(sal,15,'$') "SALARY" 
from EMP;

6.SELECT INITCAP(ename) as "Name",  LENGTH(ename) as "Name length"
FROM emp
WHERE ENAME LIKE 'J%' or ENAME LIKE 'A%' ENAME LIKE 'M%';

LENGTH(TRIM(...)) //TRIM SCOATE SPATIILE
daca numele e char => toate vor avea aceeasi lungime

7.SELECT ename, hiredate, TO_CHAR(hiredate, 'DAY') AS "Day"
FROM emp
ORDER BY TO_CHAR(hiredate ,'d');

8.SELECT ENAME,decode(comm,0,'No Comission',Null,'No Comission',to_char(comm)) "COMM"
from EMP;

Setul 2

1.SELECT ENAME "Nume",decode(deptno,10,'NEW YORK',20,'DALLAS',30,'CHICAGO',40,'BOSTON') "Oras de lucru"
from EMP;

2.SELECT ENAME,SYSDATE-hiredate "Numar de zile lucrate",job "Job",COMM
from EMP
WHERE COMM=0 or COMM is null;

3.select  translate(ename, 'y|', '|y')
FROM emp;

4.SELECT ENAME,ADD_MONTHS(HIREDATE,32*12) "Marire",months_between(sysdate,ADD_MONTHS(HIREDATE,32*12)) "Luni pana la marire", SAL*1.1 "Salariul marit"
from EMP;

5.SELECT ENAME,sal*power(1.0001,abs(months_between(HIREDATE,TO_DATE'01-01-2000'))) "Salariul nou",sal "Salariul vechi"
from EMP;

6.SELECT INITCAP(ENAME) "Nume",sal "Salariul vechi",decode(COMM,0,round(sal*power(1.001,Round((SYSDATE-hiredate)/365,0)),2),NULL,round(sal*power(1.001,Round((SYSDATE-hiredate)/365,0)),2),round(sal*power(1.0005,Round((SYSDATE-hiredate)/365,0)),2)) "Salariu marit"
from EMP;
 

 select ename,add_months(hiredate,12*32)data_maririi,round(months_between(add_months(hiredate,12*32),sysdate))asteptare,sal*1.10 salariu_marit from emp order by ename;