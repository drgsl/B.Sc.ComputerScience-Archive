--1.Write a query to display the employee name and hire date for all employees in the same department as Blake. Exclude Blake.
select ename,deptno,hiredate
from emp
where deptno in
  (select deptno
  from emp
  where ename='Blake')
and ename!='Blake' 

--2.Create a query to display the employee number and name for all employees who earn more than the average salary. 
--Sort the results in descending order of salary.
select empno,ename,lpad(sal,7)alary
from emp
where sal>
  (select avg(sal)
  from emp)
order by sal desc

--3.Write a query that will display the employee number and name for all employees who work in a
--department with any employee whose name contains a t.
select deptno,empno,ename
from emp
where deptno in
  (select deptno
  from emp
  where ename like '%t%')
order by deptno,ename

--4.Display the employee name, department number, and job title for all employees whose department location is Dallas
select ename,deptno,job
from emp
where deptno =
  (select deptno 
  from dept 
  where loc='Dallas')
order by job  
--varianta fara subinterogare
select ename,e.deptno,job
from emp e inner join dept d on e.deptno=d.deptno
where loc='Dallas'
order by job

--5.Display the employee name and salary of all employees who report to King
select ename,mgr,lpad(sal,7)salary
from emp 
where mgr =  
  (select empno
  from emp
  where ename='King')
order by salary  

--6.Display the department number, name, and job for all employees in the Sales department
select deptno,ename,job
from emp
where deptno =
  (select deptno
  from dept
  where dname='sales')
order by ename  
--varianta fara subinterogare
select e.deptno,ename,job
from emp e inner join dept d on d.deptno=e.deptno
where dname='sales'
order by ename

--7.Display the employee number, name, and salary for all employees who earn more than the
--average salary and who work in a department with any employee with a T in their name.
select deptno, empno,ename,lpad(sal,7)salary
from emp
where sal >
  (select avg(sal)
  from emp)
and deptno in
  (select deptno
  from emp
  where ename like '%t%')
order by deptno,ename 

--8.Write a query to display the name, department number and salary of any employee whose
--department number and salary matches both the department number and salary of any employee who earns a commission
select ename,deptno,lpad(sal,7)sal
from emp 
where (deptno,sal) in
  (select deptno,sal
  from emp
  where comm is not null)
order by sal

--9.Display the name, department name, and salary of any employee whose salary and commission
--matches both the salary and commission of any employee located in Dallas
select ename,dname,lpad(sal,7)salary
from emp e inner join dept d on e.deptno=d.deptno
where (sal,nvl(comm,0)) in
  (select sal,nvl(comm,0)
  from emp e inner join dept d on e.deptno=d.deptno
  where loc='Dallas')
order by sal

--10.Create a query to display the name, hire date, and salary for all employees who have both the same salary and commission as Scott
select ename,hiredate,lpad(sal,7)sal
from emp
where (sal,nvl(comm,0)) in
  (select sal,nvl(comm,0)
  from emp
  where ename='Scott') 
and ename<>'Scott'  
  
--11.Create a query to display the employees that earn a salary that is higher than the salary of any
--of the CLERKS. Sort the results on salary from highest to lowest
select ename,job,lpad(sal,7)salary
from emp
where sal>all
  (select sal
  from emp
  where job='clerk')
order by sal desc

--12.Write a query to display the top three earners in the EMP table. Display their names and salaries
select ename,lpad(sal,7)salary
from
  (select ename,sal
  from emp
  order by sal desc)
where rownum <=2
--
select ename,lpad(sal,7)salary
from emp 
where sal>
  (select max(sal)
  from emp
  where sal<
    (select max(sal)
    from emp
    where sal<
      (select max(sal)
      from emp)))
order by sal desc  

--13.Find all employees who are not a supervisor.
--a. Do this using the EXISTS operator first.
--b. Can this be done using the IN operator? Why, or why not?
--operatorul exists verifica existenta unei valori in setul de rezultate al unei subinterogari
--daca subinterogarea intoarce un rand atunci conditia de cautare nu mai continua in interogarea principala, iar conditia este marcata ca fiind true
--daca subinterogarea nu intoarce nici un rand atunci conditia este marcata ca fiind false, iar conditia de cautare continua in interogarea
--principala
--operatorul not exists testeaza daca o valoare gasita de interogarea principala este sau nu parte a setului de rezultate dat de subinterogare
select ename,empno
from emp e
where not exists 
  (select 'X' 
  from emp 
  where e.empno=mgr)
order by ename
--sau
select e1.ename,e1.empno
from emp e1
where not exists
  (select empno
  from emp e2
  where e2.mgr=e1.empno)
order by e1.ename  
--varianta cu not in
select ename,empno
from emp e
where empno not in 
  (select mgr
  from emp 
  where mgr=e.empno)
order by ename
--
select ename,empno
from emp 
where empno not in 
  (select mgr
  from emp 
  where mgr is not null)
order by ename

--14.Write a query to find all employees who make more than the average salary in their
--department. Display employee number, salary, department number, and the average salary for
--the department. Sort by average salary.
select ename,lpad(sal,7)sal,deptno,
  lpad((select round(avg(sal))from emp e1 where e1.deptno=e.deptno),7)avg_sal
from emp e
where sal > 
  (select round(avg(sal))
  from emp e1 
  where e1.deptno=e.deptno)
order by avg_sal desc
--sau
select ename, sal, deptno, avg_sal
from
(select ename, sal, deptno, 
    lpad(round(avg(sal) over (partition by deptno)),7) avg_sal
  from emp)
where sal > avg_sal
order by avg_sal desc
--sau
select e1.ename,e1.sal,e1.deptno,lpad(round(avg(e2.sal)),7) as avg_sal
from emp e1 inner join emp e2 on e1.deptno=e2.deptno
group by e1.ename,e1.sal,e1.deptno      
having e1.sal > round(avg(e2.sal))
order by avg_sal desc

--15.Write a query to display employees who earn less than half the average salary in their department
select ename,dname,d.deptno,lpad(e1.sal,7)sal
from emp e1 inner join dept d on e1.deptno=d.deptno 
where e1.sal <
  (select avg(e2.sal/2)
  from emp e2
  where e1.deptno=e2.deptno)
order by ename 
--daca nu vrem sa afisam si numele departamentului nu mai facem join in selectul principal
select ename,deptno,lpad(e1.sal,7)sal
from emp e1 
where e1.sal <
  (select avg(e2.sal/2)
  from emp e2
  where e1.deptno=e2.deptno)
order by ename 

--16.Write a query to display employees who have one or more co-workers in their department with later hiredates but higher salaries
select ename
from emp e
where sal < any
  (select c.sal
  from emp c where c.deptno=e.deptno
  and c.hiredate > e.hiredate)
order by ename
