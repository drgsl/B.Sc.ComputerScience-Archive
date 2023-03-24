--nici un index
select * from user_indexes;
select * from emp where empno=7369; --vizualizare plan si costuri fara indecsi

--adauga constrangere cheie primara
alter table emp add constraint pk Primary key(empno);

--indecsi generati automat la constrangeri unique (deci inclusiv chei primare)
select * from user_indexes;
select * from user_ind_columns where table_name = 'EMP'; --pentru a vedea coloanele indexate
select * from USER_IND_EXPRESSIONS where table_name = 'EMP'; --pentru indecsi creati pe functii - returneaza expresia
-- costuri dupa indexare
select * from emp where empno=7369; --vizualizare plan si costuri cu indecsi

alter table emp drop constraint pk;

---------------------join 
select * from emp, dept where dept.deptno = emp.deptno;--vizualizare plan join fara indecsi

----plan de executie join dupa creare index - ca urmare a declararii cheii primare ---------
alter table dept add constraint pk primary key (deptno);
select * from emp, dept where dept.deptno = emp.deptno; -- vizualizare plan join si cost cu index

--------interogare cu selectie cu functie-------
create index idx_name on emp(ename);
select * from emp where upper(ename) = 'SCOTT';--planul nu utilizeaza indexul pe ename

create index idx_name_f on emp(upper(ename));
select * from emp where upper(ename) = 'SCOTT'; -- planul utilizeaza indexul pe functie
select * from emp where upper(ename) like 'SC%';-- planul utilizeaza indexul pe functie
select * from emp where upper(ename) like '%OTT'; -- planul NU utilizeaza indexul pe functie
---------bitmap index ----------
create bitmap index idx_bit on emp(deptno); --nu e suportat in Oracle Express Edition, e necesar Enterprise edition

-------index multicheie
create index idx_job_name on emp(job, ename);
select* from emp where job='CLERK'; --utilizeaza indexul
select* from emp where job='CLERK' and ename = 'SCOTT'; -- --utilizeaza indexul
DROP INDEX idx_job_name;

---------stocare plan in baza de date - este adaugat automat in tabela plan_table; 
--dar se poate genera un alt tabel in prealabil care sa stocheze planul
EXPLAIN PLAN 
    SET STATEMENT_ID = 'all'
--    INTO new_table
    FOR SELECT distinct ename FROM emp;

----afisare plan utilizand outputul de la o procedura stocata dedicata inspectarii planurilor
select * from table(dbms_xplan.display);-- where statement_id=''all'; 
----afisare plan direct din tabelul dedicat-------
select * from plan_table;
