
select max(sal) as "Max", min(sal) as "Min",sum(sal) as "sum",avg(sal) as "Average" from emp

/
select job,max(sal) as "Max" ,min(sal) as "Min",sum(sal) as "Sum",avg(sal) as "Average" from emp group by job
/
select job,count(*) from emp group by job
/
select count(mgr) as "Number of Managers" from emp where job='MANAGER'
/
select (max(sal)-min(sal)) as "Difference" from emp
/

select mgr,min(sal) from emp where mgr is not NULL group by mgr having min(sal)>=1000 order by min(sal) desc
/
select dept.dname,dept.loc,count(*)Number_of_people, avg(sal)Salary from dept,emp where dept.deptno=emp.deptno group by dept.dname,dept.loc
/
select count(hiredate) as "Total",
count(decode(to_char(hiredate,'YYYY'),1980,'c1'))"1980",
count(decode(to_char(hiredate,'YYYY'),1981,'c2'))"1981",
count(decode(to_char(hiredate,'YYYY'),1982,'c3'))"1982",
count(decode(to_char(hiredate,'YYYY'),1983,'c4'))"1983"
from emp
/
select job,
sum(decode(deptno,10,sal))"dept 10",
sum(decode(deptno,20,sal))"dept 20",
sum(decode(deptno,30,sal))"dept 30",
sum(sal)"Total"
from emp group by job
/
