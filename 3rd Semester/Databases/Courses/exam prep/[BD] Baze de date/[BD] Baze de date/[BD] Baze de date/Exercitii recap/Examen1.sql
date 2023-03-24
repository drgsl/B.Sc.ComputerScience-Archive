/*Subiectul 1
========================
Consideram o firma de vinzari cu mai multi angajati (tabela VINZATOR). Fiecare din ei poate avea unul 
sau mai multi clienti (tabela... evident... CLIENTI). Acestia cumpara pe baza de factura (tabela FACTURI).
Pe fiecare factura sunt unul sau mai multe produse care se regasesc in tabela PRODUSE.
Avem urmatoarele tabele cu structurile si constringerile aferente:

VINZATOR
	ID_VIND (NUMBER, 4) cheie primara,
	NUME (VARCHAR2,25) 
	MARCA_SEF(NUMBER,4) referinta la ID_VIND,
	COMM (NUMBER,7,2),
	TARGET (NUMBER,6)

CLIENT
	ID_CLIENT (NUMBER,4) cheie primara,
	NUME(VARCHAR2,25)
	REP_VIND(NUMBER,4) NOT NULL, referinta externa la ID_VIND 
	CREDITLIMIT(NUMBER,8,2) 
	care indeplineste  conditia CREDITLIMIT>0

PRODUSE
	PROD_ID (NUMBER,5) cheie primara
	NUME_PROD (VARCHAR2,40) NOT NULL
	PRET (NUMBER,8,2) 

FACTURI
	ID_CLIENT(NUMBER,4) referinta externa la ID_CLIENT din CLIENTI
	NR_ORDIN(NUMBER,4) NOT NULL,
	NR_CRT(NUMBER,3) NOT NULL,
	ID_PROD (NUMBER,5) referinta externa la PROD_ID 
	QTY (NUMBER,4) NOT NULL,
	TOTAL (NUMEBR,9,2) unde
	 TOTAL=QTY*PRET (pretul produsului aferent din PRODUSE)
	Cheia primara este data de perechea (NR_ORDIN,NR_CRT)

Creati tabelele de mai sus, precum si  constringerile precizate.
Introduceti maxim 5-6 articole in fiecare tabela, folosind comanda INSERT, cu respectarea constringerilor 
aferente.*/
drop table facturi;
drop table produse;
drop table client;
drop table vinzator 
/
create table vinzator(
  id_vind number(4)
    constraint pk_id_vind primary key
    constraint nn_id_vind not null,
  nume 	varchar2(25),
  marca_sef number(4),
  comm 	number(7,2),
  target 	number(5),
    constraint fk_marca_sef foreign key(marca_sef) references vinzator(id_vind))
/
create table client(
  id_client number(4) 
    constraint pk_id_client1 primary key
    constraint nn_id_client not null,
  nume 	varchar2(25),
  rep_vind 	number(4) not null,
  creditlimit number(8,2) 
    constraint ck_creditlimit check (creditlimit>0),
  constraint rep_vind foreign key(rep_vind) references vinzator(id_vind))
/
create table produse(
  prod_id number(5) 
    constraint pk_prod_id primary key
    constraint nn_prod_id not null,
  nume_prod varchar2(40) not null,
  pret number(8,2))
/
create table facturi(
  id_client number(4),
  nr_ordin number(4) not null,
  nr_crt number(4) not null,
  id_prod	number(5),
  qty	number(4) not null,
  total	number(9,2),
    constraint pk_nr_ordin_nr_crt primary key(nr_ordin,nr_crt),
    constraint fk_id_client	foreign key(id_client) references client(id_client),
    constraint fk_id_prod	foreign key(id_prod) references produse(prod_id))
/
insert into vinzator values(10,'abcd',null, 9.5,100);
insert into vinzator values(20,'abccd',10,null,100);
insert into vinzator values(30,'abddd',20,null,100); 
insert into vinzator values(40,'sica',10,null,100);
insert into vinzator values(50,'gica',20,12.5,100) 
/
insert into client values(100,'bubu',10,1000);
insert into client values(110,'cucu',40,1500);
insert into client values(120,'dudu',40,200);
insert into client values(130,'nucu',50,2000);
insert into client values(140,'ducu',50,2100)
/
insert into produse values(1000,'mingi',10.2);
insert into produse values(1100,'adidasi',100.2);
insert into produse values(1200,'hirtie',9.2);
insert into produse values(1300,'creioane',1.2);
insert into produse values(1400,'radiera',3.2) 
/
insert into facturi values(100,1,1,1000,10,102);
insert into facturi values(110,1,2,1300,20,24);
insert into facturi values(110,1,3,1400,100,320);
insert into facturi values(120,2,1,1100,20,2004);
insert into facturi values(120,2,2,1200,100,920) 
/


/*Subiectul 2
========================
Sa se afiseze clientul care comanda cea mai multa marfa d.p.d.v valoric (clientul cu suma totalurilor 
preturilor de pe factura maxim). Stergeti tabelele create !!*/

/*Subiectul 3
========================
Sa se afiseze numele departamentelor (dept_name din dept) in care lucreaza angajatii si 
media salariala pe fiecare departament. Veti numi coloanele Departament, respectiv Avg_Sal, exact cu aceste tip de 
caractere. Rotunjiti la valoarea superioara fara nici o zecimala.*/
select dname Departament,lpad(round(avg(sal)),7) Avg_Sal
from dept d inner join emp e on d.deptno=e.deptno
group by dname
order by Avg_Sal


/*Subiectul 4
========================
Folosind clauza WITH afisati ultimii 2 angajati in firma d.p.d.v al datei de angajare (adica data de angajare 
cea mai recenta)*/
with
angajat1 as 
  (select ename,empno,hiredate
  from emp
  where hiredate in 
    (select max(hiredate)
    from emp)),
angajat2 as 
  (select ename,empno,hiredate
  from emp 
  where hiredate in 
    (select max(hiredate) 
    from emp
    where empno not in 
      (select empno 
      from angajat1))
)
select ename,hiredate
from emp
where empno in 
  (select empno 
  from angajat1) 
  or empno in 
    (select empno 
    from angajat2)
/

/*Subiect 5
========================
Sa se preia de la tastatura numele (ename) unui reprezentant vinzari (cei cu functia 'Salesman') si 
numarul unui departament (altul decit cel in care lucreaza angajatul dat anterior !)
Sa se modifice comisionul angajatilor din departamentul respectiv, ca fiind egal cu
comisionul reprezentantului de vinzari dat in primul parametru.
Afisati numele angajatilor din noul departament si noul comision doar pentru inregistrarile modificate !!
Reveniti la datele initiale. Afisati si acum pentru verificare.
Obs. veti folosi de 2 ori comanda Accept pentru fiecare parametru !*/


