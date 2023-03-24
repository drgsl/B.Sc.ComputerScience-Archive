1.select emp1.ename,emp1.hiredate from emp emp1,emp emp2where upper(emp2.ename)='BLAKE' and emp2.deptno=emp1.deptno and upper(emp1.ename)!='BLAKE';

2.select empno,enamefrom emp where sal>(select avg(sal) from emp) order by sal desc;

3.select empno,ename,deptno from emp where deptno in (select deptno from emp where ename like '%T%');

4.select ename,deptno,job from emp where deptno in (select deptno from dept where upper(loc)='DALLAS');

5.select ename,sal from emp where mgr in (select empno from emp where ename='KING');

6.select deptno,ename,job from emp where deptno in (select deptno from dept where dname='SALES');

7.select empno,ename,sal from emp where sal>(select avg(sal) from emp)  and deptno in (select deptno from emp where ename like '%T%');

8.select ename,deptno,sal from emp where deptno in (select deptno from emp where comm>0)  and sal in (select sal from emp where comm>0);

9.select ename,dname,sal from emp,dept where (nvl(comm,0),sal) in (select nvl(comm,0),sal from emp,dept where emp.deptno=dept.deptno and dept.loc='DALLAS') and emp.deptno=dept.deptno;

10.select ename,hiredate,sal where (sal,nvl(comm,0)) in (select sal,nvl(comm,0) from emp where ename='SCOTT');

11.select ename from emp where sal>all((select sal from emp where job='CLERK')) order by sal desc;