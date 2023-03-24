1.select ename,hiredate,sal from emp where (sal,nvl(comm,0)) in (select sal,nvl(comm,0) from emp where ename='SCOTT');

2.select ename from emp where empno not in(select empno from emp where empno in (select mgr from emp));

sau

select o.ename from emp o where not exists(select empno from emp i where i.mgr=o.empno);

3.select a.empno,a.sal,a.deptno,(select avg(b.sal) from emp b where a.deptno=b.deptno) "AVG" from emp a where a.sal>(select avg(e.sal) from emp e where e.deptno=a.deptno ) order by AVG ;

4.select ename,sal from emp a where a.sal<0.5*(select avg(b.sal) from emp b where b.deptno=a.deptno);

5.select ename,hiredate,sal from emp a where exists(select deptno from emp b where a.deptno=b.deptno and a.hiredate<b.hiredate and a.sal<b.sal);
