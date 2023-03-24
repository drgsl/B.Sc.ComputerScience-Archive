explain plan 
set statement_id = 'idunu' for
select * from ANIMAL where IDANIMAL=5; 

explain plan 
set statement_id = 'join' for
select * from ANIMAL, FisaAnimal where ANIMAL.IDAnimal = FisaAnimal.IDAnimal ;

--adauga constrangere cheie primara
ALTER TABLE ANIMAL add constraint pk Primary key(IDANIMAL);
ALTER TABLE FisaAnimal add constraint pk1 Primary key (IDFisa,IDAnimal);
ALTER TABLE FisaAnimal ADD CONSTRAINT Ref_FisaAnimal_to_Animal FOREIGN KEY (IDAnimal)
	REFERENCES Animal(IDAnimal);

----------cu index

--------------costuri si plan cu where
SELECT PLAN_TABLE_OUTPUT FROM TABLE(DBMS_XPLAN.DISPLAY(NULL, 'idunu','TYPICAL'));

---------------------costuri si plan cu join 
SELECT PLAN_TABLE_OUTPUT FROM TABLE(DBMS_XPLAN.DISPLAY(NULL, 'join','TYPICAL'));


--elimina constrangere cheie primara
ALTER TABLE FisaAnimal DROP CONSTRAINT REF_FISAANIMAL_TO_ANIMAL ;
alter table ANIMAL drop constraint pk;
ALTER TABLE FisaAnimal DROP CONSTRAINT pk1;

explain plan 
set statement_id = 'idunu' for
select * from ANIMAL where IDANIMAL=5; 

explain plan 
set statement_id = 'join' for
select * from ANIMAL, FisaAnimal where ANIMAL.IDAnimal = FisaAnimal.IDAnimal ;

-----------fara index

--------------costuri si plan cu where
SELECT PLAN_TABLE_OUTPUT FROM TABLE(DBMS_XPLAN.DISPLAY(NULL, 'idunu','TYPICAL'));

---------------------costuri si plan cu join 
SELECT PLAN_TABLE_OUTPUT FROM TABLE(DBMS_XPLAN.DISPLAY(NULL, 'join','TYPICAL'));

--refacem constrangeri la starea lor initiala
ALTER TABLE ANIMAL add constraint pk Primary key(IDANIMAL);
ALTER TABLE FisaAnimal add constraint pk1 Primary key (IDFisa,IDAnimal);
ALTER TABLE FisaAnimal ADD CONSTRAINT Ref_FisaAnimal_to_Animal FOREIGN KEY (IDAnimal)
	REFERENCES Animal(IDAnimal);

--------interogare cu selectie cu functie-------

DROP INDEX idx_name_f;

explain plan 
set statement_id = 'upper_username_1' for
select * from ANIMAL where upper(NUME) = 'REX';--planul utilizeaza indexul pe NUME

 explain plan 
set statement_id = 'upper_username_2' for
select * from ANIMAL where upper(NUME) like 'RE%';-- planul utilizeaza indexul pe functie

explain plan 
set statement_id = 'upper_username_3' for
select * from ANIMAL where upper(NUME) like '%EX'; -- planul NU utilizeaza indexul pe functie

SELECT PLAN_TABLE_OUTPUT FROM TABLE(DBMS_XPLAN.DISPLAY(NULL, 'upper_username_1','TYPICAL'));
SELECT PLAN_TABLE_OUTPUT FROM TABLE(DBMS_XPLAN.DISPLAY(NULL, 'upper_username_2','TYPICAL'));
SELECT PLAN_TABLE_OUTPUT FROM TABLE(DBMS_XPLAN.DISPLAY(NULL, 'upper_username_3','TYPICAL'));

create index idx_name_f on ANIMAL(upper(NUME));

SELECT PLAN_TABLE_OUTPUT FROM TABLE(DBMS_XPLAN.DISPLAY(NULL, 'upper_username_1','TYPICAL'));
SELECT PLAN_TABLE_OUTPUT FROM TABLE(DBMS_XPLAN.DISPLAY(NULL, 'upper_username_2','TYPICAL'));
SELECT PLAN_TABLE_OUTPUT FROM TABLE(DBMS_XPLAN.DISPLAY(NULL, 'upper_username_3','TYPICAL'));
