/*1. Creati o tabela numita PERSONAL conform specificatiilor urmatoare:

--------------------------------------------------------------------------------------
| Nume coloana       | ID_NUME       | LAST_NAME    | HIRE_DATE      |        TIP    |
--------------------------------------------------------------------------------------
| Tipul de cheie     |    PK         |              |                |               |
--------------------------------------------------------------------------------------
| Null/Unique        |    NN         |              |                |               |
--------------------------------------------------------------------------------------
| Implicit           |               |              |   data sistem  |               |
--------------------------------------------------------------------------------------
| Tip de data        |  NUMBER       |  VARCHAR2    |  DATE          |     CHAR      |
--------------------------------------------------------------------------------------
| Lungime            |    10         |    25        |    25          |       6       |
--------------------------------------------------------------------------------------
|Check               |               |              |                |  PENS,SOMER   |
--------------------------------------------------------------------------------------
Modificati tabela PERSONAL prin adaugarea unei coloane SALAR (NUMBER(6)) si o 
constringere de tip not null pentru aceasta.
Vizualizati constringerile (constraint_name), coloanele asociate 
(column_name) si tipul lor (constraint_type) folosind tabelele 
user_constraints si user_cons_columns intr-o singura interogare !!
Stergeti constringerea nou creata. Stergeti constringerea de la coloana TIP. Stergeti tabelul.*/
create table personal(
  id_nume number(10)
    constraint pk_id_nume primary key
    constraint nn_id_nume not null,
  ename varchar2(25),
  hire_date date
    default sysdate,
  tip char(6)
    constraint ck_tip check(tip in ('pens','somer')));
--
alter table personal add(salar number(6) constraint nn_salar not null);
--
column constraint_name format A20
column column_name format A20
column constraint_type format A15
select a.constraint_name,column_name,constraint_type
from user_constraints a inner join user_cons_columns b on a.constraint_name=b.constraint_name
and a.table_name=b.table_name
and a.table_name='PERSONAL';
--
alter table personal drop constraint nn_salar;
--
alter table personal drop constraint ck_tip;
--
drop table personal;

/*2. Afisati numele (ename), data angajarii si gradul de salarizare pentru salariatii 
veniti in firma in luna iunie precum si pentru cei veniti dupa anul 1982 inclusiv. 
Veti numi coloanele Nume, DataAng, Grad exact in aceasta forma.
Afisarea se va face descrescator dupa data angajarii.*/
select ename Nume,hiredate DataAng,grade Grad
from emp e inner join salgrade s on e.sal between s.losal and s.hisal
where hiredate like '%JUN%' or to_char(hiredate,'yyyy')>=1982
order by hiredate;

/*3. Afisati numele angajatilor (ename), numele departamentului si o adresa de mail de forma:
"ename+'_'+(primele 2 caractere din loc)+@(primele 3 caractere din numele departamentului)*/
select ename,dname, 
ename||'_'||substr(loc,1,2)||'@'||substr(dname,1,3)Mail
from emp e left outer join dept d on e.deptno=d.deptno
order by empno;














