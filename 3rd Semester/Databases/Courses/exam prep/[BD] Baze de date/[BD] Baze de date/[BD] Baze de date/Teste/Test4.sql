/*Creati o tabela numita CONCEDII conform specificatiilor urmatoare:
---------------------------------------------------------------------------
| Nume coloana    |        MARCA  	|     NUME     |  ZILECO   |  ZILECM  | 
---------------------------------------------------------------------------
| Tipul de cheie  |        PK       |      FK      |     	     |          |
---------------------------------------------------------------------------
| Null/Unique     |        NN     	|              |           |          | 
---------------------------------------------------------------------------
| Implicit        |                 |              |     0     |    0     |
---------------------------------------------------------------------------
| Tip de data     |    NUMBER  	|  VARCHAR2    |  NUMBER       | NUMBER   |
---------------------------------------------------------------------------
| Lungime         |        10       |      25      |      3    |     3    |
---------------------------------------------------------------------------
Coloana nume se leaga de coloana ename din tabela emp.
Modificati tabela, adaugind o coloana luna (number(3))) si o constringere  not null 
pentru aceasta.
Vizualizati constringerile (CONSTRAINT_NAME), coloanele asociate 
(COLUMN_NAME) si tipul lor (CONSTRAINT_TYPE) folosind tabelele 
USER_CONSTRAINTS si USER_CONS_COLUMNS intr-o singura interogare !!
Stergeti constringerea nou creata. Stergeti constringerea de la coloana nume. Stergeti tabelul.*/
create table concedii(
  marca number(10) 
    constraint pk_marca primary key
    constraint nn_marca not null,
  nume varchar2(25),
  zileco number(3)
    default 0,
  zilecm number(3)
    default 0,
  constraint fk_nume foreign key(nume) references emp(ename));
    
/*2.Afisati numele angajatului (ename), numele departamentului, venitul lunar 
(salariul plus comision) pentru toti angajaþii din firma (inclusiv cei care nu au comision !!)
Veti numi coloanele Nume, DepNume si Venit exact in aceasta forma.
Asigurati-va ca apar toti angajatii !!
Sa se ordoneze descrescator dupa venitul lunar*/
select ename Nume,dname DepNume,sal+sal*(nvl(comm,0)) Venit
from emp e inner join dept d on d.deptno=e.deptno 
order by Venit desc;

/*3. Sa se afiseze angajatii (ename) si o adresa de mail de
forma: initiala numelui+"_"+"@"+codul functiei.*/
select ename, substr(ename,1,1)||'_'||'@'||job Mail
from emp e inner join dept d on e.deptno=d.deptno
order by ename
