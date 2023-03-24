/**************************************************************
  definirea si utilizarea view-urilor
  functioneaza in SQLite, MySQL, Postgres si Oracle
**************************************************************/

/**************************************************************
  view simplu
  sID si Universitatea pentru cei acceptati la Informatica
**************************************************************/
drop view CSAccept;
create view CSaccept as
select sID, uNume
from Aplica
where specializare = 'Informatica' and decizie = 'DA';

select * from CSaccept;

/**************************************************************
  interogarea view-ului
  Studentii acceptati la Informatica la Cuza cu medie < 9.80
**************************************************************/

select Student.sID, sNume, medie
from Student, CSaccept
where Student.sID = CSaccept.sID and uNume = 'Cuza' and medie < 9.80;

/**************************************************************
  similar cu crearea unui tabel temporar
**************************************************************/
drop table T;
create global temporary table T as
select sID, uNume
from Aplica
where specializare = 'Informatica' and decizie = 'DA';

select Student.sID, sNume, medie
from Student, T
where Student.sID = T.sID and uNume = 'Cuza' and medie < 9.80;

drop table T;

/**************************************************************
  rescrierea automata a interogarii
**************************************************************/

select Student.sID, sNume, medie
from Student,
     (select sID, uNume from Aplica
      where specializare = 'Informatica' and decizie = 'DA') CSaccept
where Student.sID = CSaccept.sID and uNume = 'Cuza' and medie < 9.80;

/**************************************************************
  rescrierea automata optimizata
**************************************************************/

select Student.sID, sNume, medie
from Student, Aplica
where specializare = 'Informatica' and decizie = 'DA'
and Student.sID = Aplica.sID and uNume = 'Cuza' and medie < 9.80;

/**************************************************************
  view-uri definite pe baza altor view-uri
  studentii acceptati la Informatica la Petre Andrei cu dimLiceu > 500
**************************************************************/

create view CSPA as
select Student.sID, sNume, medie
from Student, CSaccept
where Student.sID = CSaccept.sID and uNume = 'Petre Andrei' and dimLiceu > 500;

select * from CSPA;

/**************************************************************
  interogare peste view
  studenti acceptati la Informatica la Petre Andrei cu dimLiceu > 500 si medie > 9.80
**************************************************************/

select * from CSPA where medie > 9.80;

/**************************************************************
  rescriere recursiva pentru a elimina view-urile
**************************************************************/

select * from
(select Student.sID, sNume, medie
from Student, (select sID, uNume from Aplica
               where specializare = 'Informatica' and decizie = 'DA') CSaccept
where Student.sID = CSaccept.sID and uNume = 'Petre Andrei' and dimLiceu > 500) CSsh
where medie > 9.80;

/**************************************************************
  eliminarea view-ului de baza
**************************************************************/

drop view CSaccept;
select * from CSPA;

/**************************************************************
  definirea unui mega-view cu toate datele
**************************************************************/

create view Mega as
select Universitate.uNume, oras, inscrieri,
       Student.sID, sNume, medie, dimLiceu, specializare, decizie
from Universitate, Student, Aplica
where Universitate.uNume = Aplica.uNume and Student.sID = Aplica.sID;

select * from Mega;

/**************************************************************
  nu mai sunt necesare joinuri in interogari
  
**************************************************************/

select sID, sNume, medie, uNume
from Mega
where medie > 9.50 and specializare = 'Informatica' and inscrieri > 15000;

/**************************************************************
  rescrierea interogarii fara mega-view
**************************************************************/

select Student.sID, sNume, medie, Universitate.uNume
from Universitate, Student, Aplica
where Universitate.uNume = Aplica.uNume and Student.sID = Aplica.sID
and medie > 9.50 and specializare = 'Informatica' and inscrieri > 15000;

/**************************************************************
  CLEANUP
**************************************************************/

drop view CSaccept;
drop view CSSpiru;
drop view Mega;

/************************************************************************************************
modificare view-uri cu declansatoare
  functioneaza in SQLite si Oracle
  Postgres utilizeaza sintaxa diferita pt. declansatoare
  MySQL nu suporta modificari bazate pe reguli ale view-urilor

**********************************************************************************************/
 
drop view CSAccept;
create view CSaccept as
select sID, uNume
from Aplica
where specializare = 'Informatica' and decizie = 'DA';

select * from CSaccept;
select * from Aplica;

delete from CSaccept where sID = 123; --nu e permis in SQLite, functioneaza in Oracle

drop trigger CSacceptDelete;
create trigger CSacceptDelete
instead of delete on CSaccept
for each row
begin
  delete from Aplica
  where sID = :Old.sID
  and uNume = :Old.uNume
  and specializare = 'Informatica' and decizie = 'DA';
end;

delete from CSaccept where sID = 123;

select * from CSaccept;
select * from Aplica;


/**************************************************************
  JOIN VIEW: INSERTS, DELETES, UPDATES
**************************************************************/
create view Spiru as
select Student.sID, specializare
from Student, Aplica
where Student.sID = Aplica.sID and uNume = 'Spiru Haret';

select * from Spiru;

drop trigger SpiruDelete;
create trigger SpiruDelete
instead of delete on Spiru
for each row
begin
  delete from Aplica
  where sID = :Old.sID and uNume = 'Spiru Haret' and specializare = :Old.specializare;
end;

delete from Spiru where specializare = 'Informatica';

select * from Spiru;
select * from Aplica;

drop trigger SpiruUpdate;
create trigger SpiruUpdate
instead of update on Spiru 
for each row
begin
  update Aplica
  set specializare = :New.specializare
  where sID = :New.sID and uNume = 'Spiru Haret' and specializare = :Old.specializare;
end;
 
update Spiru set specializare = 'Fizica' where specializare = 'Biologie';

select * from Spiru;
select * from Aplica;

update Spiru set sID = 321 where sID = 123;

/**************************************************************
  VIEW-uri si constrangeri
**************************************************************/


drop table Aplica;
create table Aplica(sID int, uNume varchar(20), specializare varchar(20), decizie varchar(2), unique(sID,uNume,specializare));
insert into Aplica values (123, 'Cuza', 'Informatica', 'DA');
insert into Aplica values (123, 'Cuza', 'Fizica', 'NU');
insert into Aplica values (123, 'Petre Andrei', 'Informatica', 'DA');
insert into Aplica values (123, 'Babes-Bolyai', 'Fizica', 'DA');
insert into Aplica values (234, 'Petre Andrei', 'Biologie', 'NU');
insert into Aplica values (345, 'Spiru Haret', 'Bioinginerie', 'DA');
insert into Aplica values (876, 'Spiru Haret', 'Biologie', 'DA');
insert into Aplica values (876, 'Spiru Haret', 'Informatica', 'DA');

select * from Spiru;

update Spiru set specializare = 'Informatica' where sID = 876;


/**************************************************************
  modificarea automata a view-urilor
  functioneaza in MySQL si Oracle
  SQLite si Postgres nu suporta modificarea automata
**************************************************************/

/**************************************************************
  stergere - view inerent actualizabil
**************************************************************/
drop view CSaccept;
create view CSaccept as
select sID, uNume
from Aplica
where specializare = 'Informatica' and decizie = 'DA';

select * from CSaccept;
select * from Aplica;

delete from CSaccept where sID = 123;

select * from CSaccept;
select * from Aplica;

/**************************************************************
  inserare - view inerent actualizabil
**************************************************************/
drop view CSFizica;
create view CSFizica as
select sID, uNume, specializare
from Aplica
where specializare = 'Informatica' or specializare = 'Fizica';

select * from CSFizica;

insert into CSFizica values (111, 'Spiru Haret', 'Informatica');

select * from CSFizica;
select * from Aplica;

/**************************************************************
 insertie invizibila in view
**************************************************************/

insert into CSFizica values (222, 'Spiru Haret', 'Psihologie');

select * from CSFizica;
select * from Aplica;

insert into CSAccept values(333, 'Spiru Haret');
select * from CSAccept;
select * from Aplica;

/**************************************************************
  optiunea WITH CHECK - nu permite inserari invizibile (care violeaza clauza where din definitia view-ului)
**************************************************************/
drop view CSAccept2;
create view CSaccept2 as
select sID, uNume
from Aplica
where specializare = 'Informatica' and decizie = 'DA'
with check option;

insert into CSaccept2 values (444, 'Spiru Haret');

drop view CSFizica2;
create view CSFizica2 as
select sID, uNume, specializare
from Aplica
where specializare = 'Informatica' or specializare = 'Fizica'
with check option;

insert into CSFizica2 values (444, 'Spiru Haret', 'Psihologie');
insert into CSFizica2 values (444, 'Spiru Haret', 'Informatica');

select * from CSFizica2;

/**************************************************************
  view nemodificabil datorita agregarii
**************************************************************/
drop view LiceuMedie;
create view LiceuMedie as
select dimLiceu, avg(medie) as mmedie
from Student
group by dimLiceu;

select * from LiceuMedie;

delete from LiceuMedie where dimLiceu < 500;

insert into LiceuMedie values (3000, 3.0);

/**************************************************************
  nemodificabil datorita clauzei distinct
**************************************************************/
drop view specializare;
create view specializare as
select distinct specializare from Aplica;

select * from specializare;

insert into specializare values ('Chimie');

delete from specializare where specializare = 'Informatica';

/**************************************************************
  subinterogare corelata in view 
  nu e actualizabil in MySQL, merge in Oracle 
**************************************************************/
drop view NonUnique;
create view NonUnique as
select * from Student S1
where exists (select * from Student S2
              where S1.sID <> S2.sID
              and S2.medie = S1.medie and S2.dimLiceu = S1.dimLiceu);

select * from NonUnique;

delete from NonUnique where sNume = 'Ioana';
select * from Student;
select * from Aplica;
/**************************************************************
  subinterogare necorelata
  functioneaza si in Oracle si in MySQL
**************************************************************/
drop view Bio;
create view Bio as
select * from Student
where sID in (select sID from Aplica where specializare like 'Bio%');

select * from Bio;

delete from Bio where sNume = 'Bogdan';

select * from Bio;
select * from Student;

/**************************************************************
  insertie invizibila
**************************************************************/

insert into Bio values (555, 'Karina', 9.90, 1000);

select * from Bio;
select * from Student;

/**************************************************************
  WITH CHECK OPTION
**************************************************************/
drop view Bio2;

create view Bio2 as
select * from Student
where sID in (select sID from Aplica where specializare like 'bio%')
with check option;


select * from Bio2;
insert into Bio2 values (666, 'Loredana', 9.90, 1000);

/**************************************************************
  JOIN VIEW
  nu e permisa actualizarea automata in standardul SQL
**************************************************************/
drop view Cuza;
create view Cuza(sID,aID,sNume,specializare) as
select Student.sID, Aplica.sID, sNume, specializare
from Student, Aplica
where Student.sID = Aplica.sID and uNume = 'Cuza';

select * from Cuza;

update Cuza set sNume = 'aplicant info' where specializare = 'Informatica';

select * from Cuza;
select * from Student;
select * from Aplica;

/**************************************************************
  regasirea view-urilor
**************************************************************/

select * from user_views;
select * from user_triggers; -- where base_object_type = 'VIEW';
/**************************************************************
  CLEANUP
**************************************************************/

drop view CSaccept;
drop view CSFizica;
drop view CSaccept2;
drop view CSFizica2;
drop view LiceuMedie;
drop view specializares;
drop view NonUnique;
drop view Bio;
drop view Bio2;
drop view Cuza;
drop view Cuza2;
