//------------------------------EX4 SET1
1.SELECT emp.name,emp,deptno,dept.dname
from emp,dept
where emp.deptno=dept.deptno;

2.SELECT  emp.ename, dept.dname, dept.loc
FROM emp, dept
WHERE emp.deptno=dept.deptno AND COMM>0 AND COMM IS NOT NULL;

3.SELECT emp.ename, dept.dname
FROM emp,dept
WHERE emp.ename like '%A%' and emp.deptno=dept.deptno;

4.select emp.ename, emp.job, emp.deptno, dept.dname
from emp,dept
where emp.deptno= dept.deptno and upper(dept.loc)='DALLAS';

5.SELECT worker.ename "Employee",worker.empno "Emp#",mgr.ename "Manager",mgr.empno "Mgr#"
FROM emp worker,emp mgr
where worker.mgr=mgr.empno;

6.SELECT worker.ename "Employee",worker.empno "Emp#",mgr.ename "Manager",mgr.empno "Mgr#"
FROM emp worker,emp mgr
where worker.mgr=mgr.empno(+));

7.SELECT a.ename, a.deptno, c.ename AS "Colleagues"
from emp a, emp c
where a.deptno = c.deptno AND a.ename <> c.ename

8.SELECT emp.ename, emp.job, dept.dname, emp.sal, salgrade.grade, 
from emp, dept, salgrade
WHERE emp.deptno =  dept.deptno AND emp.sal BETWEEN salgrade.losal AND salgrade.hisal

9.SELECT e.ename, e.hiredate,  
FROM emp e, emp b
WHERE UPPER(TRIM(b.ename))='BLAKE' AND e.hiredate>b.hiredate;

10. SELECT e.ename, e.hiredate, m.ename, m.hiredate
FROM emp e, emp m
WHERE e.mgr = e.empno AND e.hiredate < m.hiredate 

11.SELECT emp.name || LPAD(' ',emp.sal/100,'*') "Employee and their salaries"
FROM emp
ORDER BY emp.sal DESC;

