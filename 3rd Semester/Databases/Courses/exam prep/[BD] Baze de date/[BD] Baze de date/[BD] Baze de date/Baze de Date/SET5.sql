SELECT MAX(sal) AS "maxium", MIN(sal) as "minimum", SUM(sal) AS "sum" , ROUND(AVG(sal),2) AS "average"
FROM emp
/
SELECT Job, MAX(sal) AS "Maximum", MIN(sal) AS "Minimum", SUM(sal) AS "SUM", AVG(sal) AS "Average"
FROM emp
GROUP BY job
/
SELECT job, count(*)
FROM emp
GROUP BY job
/
SELECT COUNT(DISTINCT mgr) AS "Number of Managers" 
FROM emp
/
SELECT MAX(sal)-MIN(sal) AS "DIFFERENCE" 
FROM emp
/
SELECT mgr, MIN(sal) 
from emp 
WHERE Mgr IS NOT NULL 
GROUP BY mgr
Having MIN(sal)>=1000
ORDER BY MIN(sal) DESC
/
SELECT d.dname "Name", d.loc "Location", count(*) "Number of People", ROUND(AVG(e.sal),2) "Salary"
FROM dept d,emp e
WHERE d.deptno=e.deptno
GROUP BY d.dname,d.loc
/
SELECT COUNT(*) AS "Total number of employees",TO_CHAR(hiredate, 'yyyy') AS "HireYear"   
FROM   EMP  
WHERE TO_CHAR(hiredate, 'yyyy') in ('1980','1981','1982','1983')
GROUP BY  TO_CHAR(hiredate, 'yyyy')
/
SELECT job "Job", SUM (DECODE (deptno, 10, sal)) "Dept 10",
SUM (DECODE (deptno, 20, sal)) "Dept 20",
SUM (DECODE (deptno, 30, sal)) "Dept 30",
SUM (sal) "Total"
FROM emp
GROUP BY job 
/
