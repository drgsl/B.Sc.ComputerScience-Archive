--1.Create a query to display the name, job, hire date and employee number for each employee, with employee number appearing first.
select empno Emp#,ename Employee,job,hiredate Hire_Date 
from emp
order by hire_date

--2.Create a query to display unique jobs from emp table
select distinct job
from emp

--3.Display the name concatenated with the job, separated by a comma and space, and label the column Employee and Title
select ename || ' , ' || job as "Employee and Title"
from emp

--4.Create a query to display all the data from the emp table. Separate each column by a comma. Label the column THE_OUTPUT
select empno || ' , ' || ename || ' , ' || job || ' , ' || hiredate || ' , ' || sal as THE_OUTPUT
from emp

--5.Display the employee name, job and start date of employees hired between February 20, 1981, and May 1, 1981. 
--Order the query in ascending order of start date
select ename, job, hiredate 
from emp
where hiredate between '20-FEB-1981' and '1-MAY-1981'
order by hiredate 

--6.Display the employee name and department number of all employees in departments 10 and 30 in alphabetical order by name
select ename,deptno
from emp 
where deptno in ('10','30')
order by ename

--7.List the name and salary of employees who earn more then $1500 and are in department 10 or 30. Label the
--columns Employee and Monthly Salary, respectively.
select ename Employee,sal Monthly_Salary
from emp
where sal > 1500 and deptno in ('10','30')
order by ename

--8.Display the name and hire date of every employee who was hired in 1982
select ename,hiredate
from emp
where hiredate like '%82'

--9.Display the name and title of all employees who do not have a manager
select ename,job
from emp
where mgr is null

--10.Display the name,salary and commission for all employees who earn commissions. Sort data in descending order of salary and commissions
select ename,lpad(sal,7)salary,lpad(comm,7)commission
from emp
where comm is not null
order by sal desc,comm desc

--11.Display the name of all employees that have two Ls in their name and are in department 30 or their manager is 7782.
select ename
from emp
where ename like '%l%l%' or ename like 'L%l%' and deptno=30
union
select ename
from emp
where mgr=7782
--
select ename
from emp
where ename like '%l%l%' or ename like 'L%l%' and deptno=30 or mgr=7782
order by ename

--12.Display the name, job, salary for all employees whose job is Clerk or Analyst and their salary is not equal to
--$1000, $3000 or $5000
select ename,job,sal
from emp
where job in ('Clerk','Analyst') and sal not in ('1000','3000','5000')

--13.Display the name, salary and commission for all employees whose commission amount is greater than their salary increased by 10%
select ename,lpad(sal,7)salary,lpad(comm,7)commission
from emp
where comm> sal*0.10




