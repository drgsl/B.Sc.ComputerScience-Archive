/*1. Creati o tabela numita FURNIZOR conform specificatiilor urmatoare:

--------------------------------------------------------------------------------------
| Nume coloana       	|     MARCA   |    NUME	   |  LOC_ID      |  D_INTRARE       |
--------------------------------------------------------------------------------------
| Tipul de cheie     	|      PK     |            |    FK        |                  |
--------------------------------------------------------------------------------------
| Null/Unique        	|      NN     |      NN    |              |                  |
--------------------------------------------------------------------------------------
| Implicit           	|             |            |              |   data sistem    |
--------------------------------------------------------------------------------------
| Tip de data        	|    NUMBER   |  VARCHAR2  |    NUMBER    |	DATE         |
--------------------------------------------------------------------------------------
| Lungime            	|       6     |      25    |      5       |                  |
--------------------------------------------------------------------------------------
Coloana loc_id este legata de coloana deptno din dept !!
Modificati tabela, adaugind o coloana cod_fiscal si constringere de cheie unica pentru 
aceasta.
Vizualizati constringerile (CONSTRAINT_NAME), coloanele asociate 
(COLUMN_NAME) si tipul lor (CONSTRAINT_TYPE) folosind tabelele 
USER_CONSTRAINTS si USER_CONS_COLUMNS intr-o singura interogare !!
Stergeti constringerea nou creata. Stergeti constringerea de la nume. Stergeti tabelul.*/
create table furnizor(
  marca number(6)
    constraint pk_marca primary key
    constraint nn_marca not null,
  nume varchar2(25)
    constraint nn_nume not null,
  loc_id number(5),
  d_intrare date
    default sysdate,
  constraint fk_loc_id foreign key(loc_id) references dept(deptno));  
--
alter table furnizor add (cod_fiscal varchar2(15) constraint un_cod_fiscal unique);
--
column constraint_name format A20
column column_name format A20
column constraint_type format A15
select a.constraint_name,column_name,constraint_type
from user_constraints a inner join user_cons_columns b on a.constraint_name=b.constraint_name
and a.table_name=b.table_name
and a.table_name='FURNIZOR';
--
alter table furnizor drop constraint un_cod_fiscal;
--
alter table furnizor drop constraint nn_nume;
--
drop table furnizor

/*2. Afisati numele angajatilor (ename), numele functiei si comisionul pentru angajatii care au comision, 
iar pentru ceilalti se va afisa 'Fara comision'. Veti numi coloanele Nume, FctNume, Comision
exact in aceasta forma. Veti ordona afisarea dupa numele functiei.*/
select ename Nume,job FctNume,lpad(nvl(to_char(comm),'Fara comision'),15)Comision
from emp
order by FctNume

/*3. Afisati numele managerilor,numele angajatilor si o adresa de mail care are forma:
"ename+primele 2 caractere din functia managerului+'@'+primele 2 caractere 
din functia angajatului)unde: primul ename este numele managerului, iar al doilea ename este numele angajatului !! 
Asigurati-va ca apar toti angajatii !!
Veti numi ultima coloana Mail.*/
select m.ename Manager,e.ename Employee,e.ename||' '||substr(m.job,1,2)||'@'||substr(e.job,1,2) Mail
from emp e left outer join emp m on e.mgr=m.empno
order by m.ename


