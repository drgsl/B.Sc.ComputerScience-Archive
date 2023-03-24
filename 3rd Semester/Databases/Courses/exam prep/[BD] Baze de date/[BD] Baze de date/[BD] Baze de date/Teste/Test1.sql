/*1.Creati o tabela numita BIBLIO conform specificatiilor urmatoare:

------------------------------------------------------------------------------
| Nume coloana  |  ID_CITITOR  |    TITLU     |       GEN    |DATA_IMPRUMUT  |
------------------------------------------------------------------------------
| Tipul de cheie|   PK , FK    |              |              |     	     |
------------------------------------------------------------------------------
| Null/Unique   |     NN       |       NN     |              |               |
------------------------------------------------------------------------------
| Implicit      |              |              |              | data sistem   |                  
------------------------------------------------------------------------------
| Tip de data   |     NUMBER   |   VARCHAR2   |  VARCHAR2    |    DATE       | 
------------------------------------------------------------------------------
| Lungime       |        6     |      40      |      10      |               |
------------------------------------------------------------------------------
Coloana id_cititor din tabela biblio se leaga de coloana empno din tabela emp.
Modificati tabela adaugind o coloana noua, sex (char(1)) si o constringere de tip check 
care sa impuna doar valorile 'M' si 'F' in aceasta coloana.
Vizualizati constringerile (CONSTRAINT_NAME), coloanele asociate 
(COLUMN_NAME) si tipul lor (CONSTRAINT_TYPE) folosind tabelele 
USER_CONSTRAINTS si USER_CONS_COLUMNS intr-o singura interogare !!
Stergeti constringerea nou creata. Stergeti constringerea aferenta coloanei TITLU.
Stergeti tabelul.
*/
create table biblio
(id_cititor number(6)
  constraint pk_biblio primary key
  constraint nn_biblio not null,
titlu varchar2(40)
  constraint nn_titlu not null,
gen varchar2(10),
data_imprumut date default sysdate,
  constraint fk_id_cititor foreign key (id_cititor) references emp(empno)
);
--
alter table biblio add (sex char(1) constraint ck_sex check (sex in ('M','F')));
--
column constraint_name format A20
column column_name format A20
column constraint_type format A15
select a.constraint_name,column_name,constraint_type
from user_constraints a inner join user_cons_columns b on a.constraint_name=b.constraint_name
and a.table_name=b.table_name
and a.table_name='BIBLIO';
--
alter table biblio drop constraint ck_sex; 
--
alter table biblio drop constraint nn_titlu;
--
drop table biblio

/*2. Afisati angajatii (ename), salariul lor, limita maxima a salariului (hisal)
 pentru cei care au gradul de salarizare 3 si 4. Gradul si limita maxima a salariului se gasesc
in tabela grades. Veti numi coloanele Nume, Salariu si MaxSal exact in aceasta forma.
Afisarea se va face in ordinea descrescatoare a salariului*/
select ename Nume,lpad(sal,7)Salariu, hisal Max_Sal
from emp e inner join salgrade s on sal between losal and hisal
where grade in (3,4)
order by sal desc

/*3. Afisati numele angajatilor, numele departamentului si o adresa de mail care are forma:
"ename_(primele 3 caractere din numele departamentului)@(primele 2 caractere din job).
Asigurati-va ca apar toti angajatii ! */
select ename,dname, 
ename||'_'||substr(dname,1,3)||'@'||substr(job,1,2)Mail
from emp e left outer join dept d on e.deptno=d.deptno
order by empno










