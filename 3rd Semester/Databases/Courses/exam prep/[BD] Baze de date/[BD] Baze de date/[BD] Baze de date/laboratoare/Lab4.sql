--1.Write a query to display the name, department number, and department name for all employees
select ename,d.deptno,dname
from emp e inner join dept d on e.deptno=d.deptno
order by deptno

--2.Write a query to display the employee name, department name, and location of all employees who earn a commission
select ename,dname,loc,lpad(comm,7)comm
from emp e inner join dept d on e.deptno=d.deptno 
where comm is not null
order by ename

--3.Display the employee name and department name for all employees who have an A in their name
select ename,dname
from emp e inner join dept d on e.deptno=d.deptno
where ename like '%a%' or ename like 'A%'
order by ename
--
select ename,dname
from emp e inner join dept d on e.deptno=d.deptno
where upper(ename) like '%A%'
order by ename

--4.Write a query to display the name, job, department number, and department name for all employees who work in Dallas
select ename,job,d.deptno,dname 
from emp e inner join dept d on
e.deptno=d.deptno 
where loc='Dallas'
order by ename

--5.Display the employee name and employee number along with their manager’s name and manager number. 
--Label the columns Employee, Emp#, Manager, and Mgr#, respectively
select e.ename Employee,e.empno Emp#,m.ename Manager,e.mgr Mgr#
from emp e inner join emp m on e.mgr=m.empno
order by e.mgr

--6.Modify the statement above to display all employees including King, who has no manager
select e.ename Employee,e.empno Emp#,m.ename Manager,e.mgr Mgr#
from emp e left outer join emp m on e.mgr=m.empno
order by e.empno,e.mgr

--7.Create a query that will display the employee name, department number, and all the
--employees that work in the same department as (are colleagues of) a given employee. Give each
--column an appropriate label
select e.ename, e.deptno, c.ename Coleg 
from emp e inner join emp c ON e.empno<>c.empno
where e.deptno=c.deptno
order by e.deptno
--sau
select e.ename, e.deptno, c.ename Coleg
from emp e inner join emp c ON e.deptno=c.deptno
where e.empno<>c.empno
order by e.deptno
--sau
select e.ename, e.deptno, c.ename Coleg 
from emp e inner join emp c ON e.deptno=c.deptno and e.empno<>c.empno
order by e.deptno

--8.Show the structure of the SALGRADE table. Create a query that will display the name, job,
--department name, salary, and grade for all employees
desc salgrade
--
select ename,job,dname,lpad(sal,7)salary,lpad(grade,5)grade
from emp e inner join dept d
on e.deptno=d.deptno inner join salgrade s on e.sal between s.losal and s.hisal
order by grade

--9.Create a query to display the name and hire date of any employee hired after employee Blake
SELECT ENAME,HIREDATE 
from emp 
where hiredate>
  (select hiredate 
  from emp 
  where ename='Blake')
order by hiredate
--
select e.ename,e.hiredate
from emp e inner join emp b on e.hiredate>b.hiredate
and b.ename='Blake' 
order by e.hiredate

--10.Display all employees’ names and hire dates along with their manager’s name and hire date
--for all employees who were hired before their managers. Label the columns Employee, Emp
--Hiredate, Manager, and Mgr Hiredate, respectively
select e.ename Employee,e.hiredate Emp_Hiredate,m.ename Manager,m.hiredate Mgr_Hiredate
from emp e inner join emp m on e.mgr=m.empno
where m.hiredate > e.hiredate
order by Mgr_Hiredate

--11.Create a query that displays the employees name and the amount of the salaries of the
--employees are indicated through asterisks (*). Each asterisk signifies a hundred dollars.
--Sort the data in descending order of salary. Label the column
--EMPLOYEE_AND_THEIR_SALARIES
SELECT ENAME EMPLOYEE,LPAD(' ',SAL/100,'*') THEIR_SALARY 
from emp 
order by sal desc

--12.Afisati angajatul cu cel mai mare salariu
--se foloseste interogare in clauza from
select *
from (select sal,ename
      from emp
      order by sal desc)
where rownum <= 2




  


