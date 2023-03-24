drop table exemplar cascade constraints;
create table exemplar(
id_exemplar int not null primary key,
nume varchar2(20),
sex varchar2(1),
greutate int,
cantitate_mancare int,
stare_medicala varchar2(15),
varsta int,
id_ingrijitor int not null,
id_zona int
);

drop table fisa_medicala cascade constraints;
create table fisa_medicala(
id_fisa int not null primary key,
id_exemplar int not null
);

drop table boli cascade constraints;
create table boli(
id_boala int not null primary key,
boala varchar2(30),
tratament varchar2(30)
);

drop table ingrijitori cascade constraints;
create table ingrijitori(
id_ingrijitor int not null primary key,
nume varchar2(20),
nr_specii int
);



alter table fisa_medicala add foreign key (id_exemplar) references exemplar(id_exemplar);
alter table exemplar add foreign key (id_ingrijitor) references ingrijitori(id_ingrijitor);

drop trigger adauga_ingrijitor;
create trigger adauga_ingrijitor after update on exemplar
for each row 
begin
update ingrijitori 
set nr_specii= nr_specii+1
where nume like '%a%';
end;


insert into ingrijitori values(100, 'cata', 1);
insert into ingrijitori values(101, 'andrei', 1);

insert into exemplar values(100, 'panda1', 'M', 23, 1, 'sanatos', 7, 100, 1);
insert into exemplar values(101, 'panda2', 'F', 26, 3, 'sanatos', 9, 101, 1);

insert into fisa_medicala values(1, 100);
insert into fisa_medicala values(2, 101);

insert into boli values(31, 'limbrici', 'sirop');
insert into boli values(23, 'paraziti', 'injectii');

drop view mancare_zilnica;
create view mancare_zilnica as select id_exemplar, nume, cantitate_mancare, id_ingrijitor, id_zona from exemplar ;

select * from exemplar;
select * from mancare_zilnica;

insert into mancare_zilnica values(103, 'panda3', 5, 100, 2);

select * from mancare_zilnica;


drop view mancare_zilnica;
create view mancare_zilnica as select id_exemplar, nume, cantitate_mancare, id_ingrijitor, id_zona from exemplar ;

select * from exemplar;
select * from mancare_zilnica;

drop trigger mancare_zilnicaDelete;
create trigger mancare_zilnicaDelete instead of delete on mancare_zilnica
for each row
begin
delete from exemplar
where id_exemplar=:old.id_exemplar;
end;

delete from mancare_zilnica where id_exemplar=103;

select * from mancare_zilnica;
select * from exemplar;



explain plan set statement_id='upper_exemplar' for select * from exemplar where upper(nume) like 'PA%';
select plan_table_output from table(DBMS_XPLAN.DISPLAY(null,'upper_exemplar','Typical'));