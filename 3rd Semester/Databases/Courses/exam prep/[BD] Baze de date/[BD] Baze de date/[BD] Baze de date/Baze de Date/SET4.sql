SELECT e.ename, e.deptno, d.dname
FROM emp e, dept d
WHERE e.deptno=d.deptno
/

SELECT e.ename, d.dname, d.loc
FROM emp e, dept d
WHERE e.deptno=d.deptno
AND e.comm IS NOT NULL
/
SELECT e.ename, d.dname
FROM emp e, dept d
WHERE e.deptno=d.deptno
AND e.ename LIKE '%A%'
/
SELECT e.ename, e.job, d.deptno, d.dname
FROM emp e, dept d
WHERE e.deptno=d.deptno
AND d.loc='DALLAS'
/
SELECT e.ename "Employee", e.empno "Emp#", m.ename "Manager", m.empno "Mgr#"
FROM emp e, emp m
WHERE e.mgr=m.empno
/
SELECT e.ename "Employee", e.empno "Emp#", m.ename "Manager", m.empno "Mgr#"
FROM emp e, emp m
WHERE e.mgr=m.empno(+)
/
SELECT e.deptno "Department", e.ename "Employee", c.ename "Colleague"
FROM emp e, emp c
WHERE e.deptno=c.deptno
/
SELECT e.ename, e.job, d.dname, e.sal, s.grade
FROM emp e, dept d, salgrade s
WHERE e.sal BETWEEN s.losal AND s.hisal
AND e.deptno=d.deptno
/
SELECT e.ename, e.hiredate
FROM emp e, emp blake
WHERE blake.ename='BLAKE'
AND e.hiredate > blake.hiredate
/
SELECT e.ename "Employee", e.hiredate "Emp Hiredate", m.ename "Manager", m.hiredate "Mgr Hiredate"
FROM emp e, emp m
WHERE e.mgr=m.empno
AND e.hiredate < m.hiredate
/
SELECT e.ename||LPAD('*',(sal/100),'*') AS EMPLOYEE_AND_THEIR_SALARIES
FROM emp e
ORDER BY sal DESC
/
