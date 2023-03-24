/*Subiectul nr.1
========================
Sa se afiseze numele departamentelor, angajatii si data de angajare pentru cei care 
s-au angajatat intr-o luna para si lucreaza intr-un departament care contine 2 de 'n'
in nume. Afisarea sa nu fie case-sensitive.*/
select dname,ename,hiredate
from emp e inner join dept d on e.deptno=d.deptno
where mod(to_char(hiredate,'mm'),2)=0 and dname like '%n%n%'

/*Subiectul nr.2
========================
Sa se afiseze managerii si suma salariilor subordonatilor lor pentru acei manageri 
care au salariul mai mic decit aceasta suma. Sa se denumeasca coloanele 
nume_manager, respectiv sum_sal si sa se ordoneze crescator dupa suma salariilor.*/


/*Subiectul 3 
========================
Creati o tabela numita DVD conform specificatiilor urmatoare:
-------------------------------------------------------------------------------
| Nume coloana     | ID_DVD       |    GEN       |   PERS_ID     |   SEDIU   |
-------------------------------------------------------------------------------
| Tipul de cheie   |    PK         |              |        FK     |    FK     |
-------------------------------------------------------------------------------
| Null/Unique      |               |     NN       |        NN     |           |
-------------------------------------------------------------------------------
| Valoare implicita|               |              |               |           |  
-------------------------------------------------------------------------------
| Tip de data      |    NUMBER     |   VARCHAR2   |     NUMBER    |  NUMBER   |
-------------------------------------------------------------------------------
| Lungime          |      5        |      20      |       5       |    5      |
-------------------------------------------------------------------------------
Coloana pers_id se leaga de coloana empno din tabela emp, iar coloana
sediu de coloana deptno din dept.
Adaugati o constringere tip check pe coloana gen, care sa permita doar introducerea valorilor:
'drama', 'comedie', 'actiune'. 
Introduceti in tabela nou creata 3-4 inregistrari cu valori  la alegere trecute explicit in comanda.
Afisati datele introduse. Stergeti constringerea nou creata. 
Stergeti datele din tabel. Stergeti tabelul.*/
create table dvd(
  id_dvd	number(5) 
    constraint pk_id_dvd primary key
    constraint nn_id_dvd not null,
  gen varchar2(20) not null,
  pers_id number(5),
  sediu number(5),
    constraint fk_pers_id foreign key(pers_id) references emp(empno),
    constraint fk_sediu foreign key(sediu) references dept(deptno))
--
alter table dvd add constraint gen_ck check(gen in ('drama', 'comedie', 'actiune'))
--
insert into dvd values(1,'drama',7839,20);
insert into dvd values(2,'actiune',7566,20);
insert into dvd values(3,'comedie',7844,10);
--
select * from dvd 
--
alter table dvd drop constraint gen_ck
--
delete from dvd 
--
drop table dvd

/*Subiectul 4
========================
Sa se afiseze numele departamentelor, angajatii si data de angajare pentru cei care 
s-au angajat intr-un an nebisect si lucreaza  intr-un departament care contine 2 de 's'
in nume. Afisarea sa nu fie case-sensitive.*/
select dname,ename,hiredate
from emp e inner join dept d on e.deptno=d.deptno
where mod(to_char(hiredate,'yyyy'),4)!=0 and lower(dname)like lower('%s%s%')

/*Subiectul 5
========================
Sa se afiseze numele departamentelor, angajatii si data de angajare pentru cei care 
s-au angajatat intr-o zi impara si lucreaza  intr-un departament care contine 2 de 'e'
in nume. Afisarea sa nu fie case-sensitive.*/
select dname,ename,hiredate
from emp e inner join dept d on e.deptno=d.deptno
where mod(to_char(hiredate,'dd'),2)=1 and lower(dname) like '%e%e%'

/*Subiectul 6
========================
Sa se afiseze managerul cu cea mai mica suma salariala a subordonatilor lui.*/


