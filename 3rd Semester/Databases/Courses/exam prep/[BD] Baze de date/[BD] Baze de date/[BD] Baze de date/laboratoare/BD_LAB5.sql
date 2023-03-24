1.SELECT round(max(sal),1) "Maximum", round(min(sal),1) "Minimum", round(sum(sal),1) "Sum", round(avg(sal),1) "Average"
from emp;

2.SELECT job, min(sal), max(sal),sum(sal), avg(sal)
from emp
group by job

3.SELECT job, COUNT(job)
from emp
group by job;

4.select count(job)
from emp
where initcap(trim(job)) = "Manager";

select count(DISTINCT mgr)
from emp;

5.select job, max(sal) - min(sal) as "DIFFERENCE"
from emp
group by job;

6.select manager.empno, min(worker.sal) "Minimum"
from emp worker, emp manager
where worker.mgr = manager.empno and worker.mgr is not null
group by manager.empno
having min(worker.sal) > 1000
order by "Minimum" desc;

7.select dept.dname, dept.loc, count(empno), avg(sal)
from emp,dept
where emp.deptno = dept.deptno
group by dname, loc;

8.SELECT count(*) , sum(decode(to_char(hiredate,'yyyy'),1980,1,0)) "1980",
                    sum(decode(to_char(hiredate,'yyyy'),1981,1,0)) "1981",
                    sum(decode(to_char(hiredate,'yyyy'),1982,1,0)) "1982",
                    sum(decode(to_char(hiredate,'yyyy'),1983,1,0)) "1983"
from emp;

9.select job as "JOB", SUM(DECODE(deptno,10,sal)) "Dep.10",SUM(DECODE(deptno,20,sal)) "Dep.20",SUM(DECODE(deptno,30,sal)) "Dep.30",sum(sal) "total"
from emp
group by job
order by job ASC;

10.//NUMELE SALARIATULUI CU CEL MAI MARE SALARIU

select a.ename, max(b.sal), a.sal
from emp a, emp b
group by  a.ename, a.sal
having a.sal = max(b.sal);
