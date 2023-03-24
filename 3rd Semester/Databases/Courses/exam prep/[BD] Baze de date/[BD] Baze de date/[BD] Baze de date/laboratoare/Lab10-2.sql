/*1.Modificati structurile de date din tabela emp astfel incat sa fortati urmatoarele constrangeri:
• Chei primare pe tabelele dept si emp
• Campul ename cheie candidat in emp
• Chei straine pentru a relationa tabelele emp-dept, emp-bonus
• Pentru tabelul salgrade hisal>losal.
Inserati in fiecare din cele 4 tabele cate o noua inregistrare.*/
--supercheie: atribut sau multime de atribute care identifica in mod unic un tuplu intr-o relatie
--cheie candidat: o supercheie cu proprietatea ca nici o submultime proprie a sa nu este supercheie
--cheie primara: o cheie candidat selectata pentru a identifica in mod unic tuplele intr-o relatie
--cheie alternativa: o cheie candidat care nu a fost selectata pentru a fi cheie primara
--cheie straina: un atribut sau o submultime de atribute dintr-o relatie care face referinta la o cheie candidat a altei relatii
drop table dept
drop table emp
drop table salgrade
drop table bonus

create table dept(
  deptno number(2),
  dname varchar2(14),
  loc varchar2(13));
alter table dept add constraint pk_deptno primary key(deptno);  
--alter table dept add constraint ck_dept_loc check(substr(loc,1,1)=upper(substr(loc,1,1)));
--
create table emp(
  empno number(4),
  ename varchar2(10),
  job varchar2(9),
  mgr number(4),
  hiredate date default sysdate,
  sal number(7,2),
  comm number(7,2),
  deptno number(2));
alter table emp add constraint pk_empno primary key(empno);  
--alter table emp add constraint ck_ename check(substr(ename,1,1)=upper(substr(ename,1,1)));
alter table emp add constraint un_ename unique(ename);
alter table emp add constraint fk_deptno foreign key (deptno) references dept (deptno);
--
create table bonus(
  ename varchar2(10),
  job varchar2(9),
  sal number(7,2),
  comm number(7,2));
alter table bonus add constraint fk_ename foreign key(ename) references emp(ename);  
--
create table salgrade(
  grade number(5),
  losal number(7),
  hisal number(7),
  tax number(5,2),
  seniority number(2));
alter table salgrade add constraint ck_salgrade check (hisal>losal);  
--
insert into dept values(10,'accounting','New York');
insert into dept values(20,'research','Dallas');
insert into dept values(30,'sales','Chicago');
insert into dept values(40,'operations','Boston');
--
insert into emp values(7369,'Smith','clerk',7902,'17-DEC-1980',800,null,20);
insert into emp values(7499,'Allen','salesman',7698,'20-FEB-1981',1600,300,30);
insert into emp values(7521,'Ward','salesman',7698,'22-FEB-1981',1250,500,30);
insert into emp values(7566,'Jones','manager',7839,'2-APR-1981',2975,null,20);
insert into emp values(7654,'Martin','salesman',7698,'28-SEP-1981',1250,1400,30);
insert into emp values(7698,'Blake','manager',7839,'01/05/1981',2850,null,30);
insert into emp values(7782,'Clark','manager',7839,'09/06/1981',2450,null,10);
insert into emp values(7788,'Scott','analyst',7566,'13/07/1981',3000,null,20);
insert into emp values(7839,'King','president',null,'17/11/1981',5000,null,10);
insert into emp values(7844,'Turner','salesman',7698,'8/09/1981',1500,0,30);
insert into emp values(7876,'Adams','clerk',7788,'13/07/1981',1100,null,20);
insert into emp values(7900,'James','clerk',7698,'3/12/1981',950,null,30);
insert into emp values(7902,'Ford','analyst',7566,'3/12/1981',3000,null,20);
insert into emp values(7934,'Miller','clerk',7782,'23/12/1982',1300,null,10);
--
insert into bonus values('Martin','salesman',1250,1400);
insert into bonus values('Ward','salesman',1250,500);
insert into bonus values('Turner','salesman',1500,0);
insert into bonus values('Allen','salesman',1600,300);

--
insert into salgrade values(1,700,1200,0.10,2);
insert into salgrade values(2,1201,1400,0.15,3);
insert into salgrade values(3,1401,2000,0.20,4);
insert into salgrade values(4,2001,3000,0.35,3);
insert into salgrade values(5,3001,9999,0.60,0);

--2. Creati un tabel denumit “EmpInfoTable” care sa contina urmatoarele informatii extrase din tabelele
--de mai sus: cod angajat, nume angajat, nume department, nume sef.
--drop table EmpInfoTable
create table EmpInfoTable(
  empno number(4)
    constraint pk_empno1 primary key,
  ename varchar2(10),
  deptno number(2),
  mgr number(4));
--  
create table EmpInfoTable as 
select empno,ename,deptno,mgr 
from emp

--3. Creati un view denumit “EmpInfoView” care sa contina informatiile de la 2. Inserati o noua
--inregistrare in tabelul emp. Afisati inregistrarile care se afla in EmpInfoView si nu exista in EmpInfoTable.
/*View-ul reprezinta subseturi de date din una sau mai multe tabele. Altfel spus view-ul este o tabela logica bazata pe o tabela sau
pe alt view, iar tabelele pe care se bazeaza un view sunt numite tabele de baza. Este stocat ca o instructiune select in dictionarul
de date.*/
--drop view EmpInfoView
create view EmpInfoView as 
  select empno,ename,deptno,mgr
  from EmpInfoTable;
 
--facem o inserare in modul interactiv
accept p_empno prompt 'Introduceti marca angajatului: '
accept p_ename prompt 'Introduceti numele angajatului: '
accept p_job prompt 'Introduceti jobul angajatului: '
accept p_mgr prompt 'Introduceti seful angajatului: '
accept p_hiredate prompt 'Introduceti data de angajare: '
accept p_sal prompt 'Introduceti salariul angajatului: '
accept p_comm prompt 'Introduceti eventualul comision al angajatului: '
accept p_deptno prompt 'Introduceti departamentul angajatului: '
begin
  insert into emp(empno,ename,job,mgr,hiredate,sal,comm,deptno) values(&p_empno,'&p_ename','&p_job',&p_mgr,'&p_hiredate',&p_sal,&p_comm,&p_deptno);
commit;
end;

--4. Creati tabelul “Student” cu campurile “Id” si “Nume”; “Id” joaca rol de cheie primara. Inserati 5
--inregistrari in care valorile cheii sunt generate cu o secventa.
create table Student(
  id number(4) 
    constraint pk_id_student_1 primary key,
  nume varchar2(40));  
--cream secventa
create sequence seq_student
  start with 100
  increment by 1
  maxvalue 2000
--inseram date in tabela student cu ajutorul secventei
insert into student values(seq_student.nextval,'Marius');
insert into student values(seq_student.nextval,'Gigi');
insert into student values(seq_student.nextval,'Maria');
insert into student values(seq_student.nextval,'Gica');
insert into student values(seq_student.nextval,'Ion');
insert into student values(seq_student.nextval,'Vasile');
--afisarea datelor
select * from student

--5. Modificati tabelul de la 4. Adaugand o noua coloana “Note” constransa sa primeasca valori intregi
--cuprinse intre 4 si 10.
alter table student add (note integer constraint ck_note check(note between 4 and 10))

--6.Creati un view care sa contina detalii despre angajatii din departamentul 30.
create view detalii_ang_dept30 as
  select empno,ename,job,sal
  from emp
  where deptno=30
  
--7.Sa se preia date din view-ul construit la exercitiul 6.
select * 
from detalii_ang_dept30
--daca nu dorim sa preluam toate informatiile
select empno,ename,job
from detalii_ang_dept30
order by ename
--afisati numele angajatilor din view-ul creat la exercitiul 6
select ename
from detalii_ang_dept30

--8.Selectati numele view-urilor si textul din dictionarul de date user_views
column view_name format a30
column text format a50
select view_name,text
from user_views

--9.Modificati view-ul construit la exercitiul 6 utilizand clauza create or replace.
--Sa se foloseasca si un alias pentru fiecare nume de coloana.
--aliasurile trebuie sa respecte ordinea coloanelor !
create or replace view detalii_ang_dept30
  (marca_angajat,nume_angajat,meserie,salariu)
as
select empno,ename,job,sal
from emp
where deptno=30

--10.Sa se creeze un view care afiseaza, pentru fiecare departament in parte, salariul minim, maxim si mediu.
--Sa se foloseasca si aliasuri
create or replace view dept_view
  (nume_departament,salariu_minim,salariu_maxim,salariu_mediu)
as 
select dname,lpad(min(sal),7),lpad(max(sal),7),lpad(round(avg(sal)),7)
from emp e inner join dept d on d.deptno=e.deptno
group by dname
order by round(avg(sal))
--
select * 
from dept_view
--
/*este interzisa stergerea unei linii atunci cand view-ul contine functii de grupare, clauza group by si cuvantul distinct*/
/*este interzisa modificarea datelor intr-un view daca acesta contine conditiile mentionate mai sus, daca are coloane definite prin 
expresii si daca contine pseudocoloana rownum*/
/*este interzisa adaugarea datelor intr-un view daca acesta contine conditiile mentionate la stergere si modificare
si daca exista coloane ce nu au voie sa aiba valori nule in tabelele de baza ce nu au fost selectate de catre view*/

--11.Sa se construiasca un view care sa afiseze marca, numele, jobul si salariul angajatilor din departamentul 20
--utilizand clauza with check option
create or replace view detalii_ang_dept20
as
select ename,job,sal,deptno
from emp
where deptno=20
with check option constraint ck_detalii_ang_dept20
--orice incercare de a modifica numarul departamentului va genera eroare deoarece incalca constrangerea with check option
--de exemplu, daca dorim ca pe angajatul cu numele Smith (presupunem evident ca nu exista decat un singur Smith !) sa il mutam in 
--departamentul 10, se genereaza o eroare:
update detalii_ang_dept20
set deptno=10
where ename='Smith'

--12.Sa se interzica orice operatiune de manipulare a datelor asupra view-ului de mai sus.
create or replace view detalii_ang_dept20
as
select ename,job,sal,deptno
from emp
where deptno=20
with read only
--incercam sa stergem o linie, se va genera eroare:
delete from detalii_ang_dept20
where ename='Smith'



