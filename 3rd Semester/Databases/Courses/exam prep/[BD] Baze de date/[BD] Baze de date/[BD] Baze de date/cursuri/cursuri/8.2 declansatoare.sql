/**************************************************************
  Declansatoare
  functioneaza in SQLite (cu modificarea dispare ':' din :OLD si :NEW - necesare pt. Oracle) 
  functioneaza in Postgres daca actiunea din trigger e specificata ca procedura stocata
  MySQL nu suporta WHEN, evenimentul UPDATE cu atribute, mai multe declansatoare pt.acelasi eveniment, inlantuirea declansatoarelor
  Oracle nu suporta interogari in clauza WHEN, nici interogari asupra tabelului la care e asociat triggerul in campul actiune
**************************************************************/

/**************************************************************
  AFTER-INSERT TRIGGER
  studentii noi cu media intre 9.00 si 9.66 aplica automat la
  Geologie la Cuza si la Biologie la Petre Andrei
**************************************************************/
drop trigger R1;
create trigger R1
after insert on Student
for each row
when (New.medie > 9.00 and New.medie <= 9.66)
begin
  insert into Aplica values (:New.sID, 'Cuza', 'Geologie', null);
  insert into Aplica values (:New.sID, 'Petre Andrei', 'Biologie', null);
end;

insert into Student values ('111', 'Constantin', 9.50, 1000);
insert into Student values ('222', 'Loredana', 9.80, 1000);
select * from Student;
select * from Aplica;



insert into Student select sID+1, sNume, medie, dimLiceu from Student;
select * from Student;
select * from Aplica;

/**************************************************************
  AFTER-DELETE TRIGGER
  Cascaded delete pentru Aplica(sID) references Student(sID)
**************************************************************/

create trigger R2
after delete on Student
for each row
begin
  delete from Aplica where sID = :Old.sID;
end;

delete from Student where sID > 100;
select * from Student;
select * from Aplica;

/**************************************************************
  AFTER-UPDATE TRIGGER
  Cascaded update pentru Aplica(uNume) references Universitate(uNume)
**************************************************************/

create trigger R3
after update of uNume on Universitate
for each row
begin
  update Aplica
  set uNume = :New.uNume
  where uNume = :Old.uNume;
end;

update Universitate set uNume = 'Al.I.Cuza' where uNume = 'Cuza';
update Universitate set uNume = 'Spiru-Haret' where uNume = 'Spiru Haret';
select * from Universitate;
select * from Aplica;

/**************************************************************
  ruleaza in SQLite
  Oracle nu permite interogari in clauza WHEN
  BEFORE TRIGGERS, actiune ce ridica erori
  forteaza constrangeri de tip cheie pentru Universitate.uNume
**************************************************************/

create trigger R4
before insert on Universitate
for each row
when (exists (select * from Universitate where uNume = New.uNume))
begin
  select raise(ignore);
end;

create trigger R5
before update of uNume on Universitate
for each row
when (exists (select * from Universitate where uNume = New.uNume))
begin
  select raise(ignore);
end;

insert into Universitate values ('Cuza', 'Iasi', 15000);
insert into Universitate values ('Petre Andrei', 'hello', 10000);
select * from Universitate;

update Universitate set uNume = 'Spiru Haret' where uNume = 'Spiru-Haret';
select * from Universitate;
update Universitate set uNume = 'Cuza' where uNume = 'Al.I.Cuza';
select * from Universitate;
update Universitate set uNume = 'Standford' where uNume = 'Al.I.Cuza';
select * from Universitate;

select * from Aplica;
delete from Universitate where uNume = 'Standford';
delete from Aplica where uNume = 'Standford';

/**************************************************************
  TRIGGER CHAINING
  cand numarul de aplicanti e mai mare ca 10, numeste Universitatea 'Done'
  interogare in when -> nu ruleaza in Oracle
**************************************************************/

create trigger R6
after insert on Aplica
for each row
when (select count(*) from Aplica where uNume = New.uNume) > 10
begin
  update Universitate set uNume = uNume || '-Done'
  where uNume = New.uNume;
end;

select count(*) from Aplica where uNume = 'Cuza';
select count(*) from Aplica where uNume = 'Petre Andrei';
select count(*) from Student where medie > 9.00 and medie <= 9.66;

insert into Student select * from Student;
select * from Universitate;
select * from Aplica;

select count(*) from Aplica where uNume = 'Cuza';
select count(*) from Student where medie > 9.00 and medie <= 9.66;

insert into Student select * from Student;
select * from Universitate;
select * from Aplica;

/**************************************************************
  mai multe triggere pe acelasi eveniment
  nu se pot insera studenti cu dimLiceu < 100 sau dimLiceu > 5000
**************************************************************/

delete from Student;
delete from Aplica;
 drop trigger R7;
create trigger R7
before insert on Student
for each row
when (New.dimLiceu < 100 or New.dimLiceu > 5000)
begin
  --select raise(ignore); --in SQLite
  raise_application_error (-20999,'dimensiune nepermisa'); --in Oracle
end;

insert into Student values ('444', 'Nancy', 9.50, 500);
insert into Student values ('555', 'Otis', 9.50, 50);
insert into Student values ('666', 'Peter', 9.50, 8000);
select * from Student;
select * from Aplica;

drop trigger R7;

create trigger R7
after insert on Student
for each row
when (New.dimLiceu < 100 or New.dimLiceu > 5000)
begin
  delete from Student where sID = :New.sID;
end;

insert into Student values ('777', 'Quincy', 9.50, 1000);
insert into Student values ('888', 'Rita', 9.50, 10000); --eroare de tip mutating table in Oracle
select * from Student;
select * from Aplica;

--find triggers
select * from user_triggers where table_name = 'STUDENT';

drop trigger R1;
drop trigger R2;
drop trigger R3;
drop trigger R4;
drop trigger R5;
drop trigger R6;
drop trigger R7;
delete from Student;
delete from Aplica;

/**************************************************************
  declansatoare complexe
  ruleaza in SQLite
  accepta automat la Spiru Haret studenti cu medii mari de la licee mari
**************************************************************/
--varianta SQLite, nu ruleaza in Oracle
create trigger AutoAccept
after insert on Aplica
for each row
when (New.uNume = 'Spiru Haret' and
      3.7 < (select medie from Student where sID = New.sID) and
      1200 < (select dimLiceu from Student where sID = New.sID))
begin
  update Aplica
  set decizie = 'DA'
  where sID = New.sID
  and uNume = New.uNume;
end;


insert into Student values (123, 'Ioana', 3.9, 1000);
insert into Student values (234, 'Bogdan', 3.9, 1500);

insert into Aplica values (123, 'Spiru Haret', 'Informatica', null);
insert into Aplica values (234, 'Spiru Haret', 'Informatica', null);
insert into Aplica values (234, 'Cuza', 'Informatica', null);
select * from Aplica;

drop trigger AutoAccept;


/**************************************************************
  cand numarul de inscrieri creste de la 16000 la peste 16000, elimina aplicatiile la
    'Fizica' si modifica deciziile pe 'U' (undecided)
**************************************************************/
drop trigger TooMany;
create trigger TooMany
after update of inscrieri on Universitate
for each row
when (Old.inscrieri <= 16000 and New.inscrieri > 16000)
begin
  delete from Aplica
    where uNume = :New.uNume and specializare = 'Fizica';
  update Aplica
    set decizie = 'U'
    where uNume = :New.uNume
    and decizie = 'DA';
end;

select * from Aplica;
select * from Universitate;
update Universitate set inscrieri = inscrieri + 2000;
select * from Aplica;

/**************************************************************
  exemplu ciclare
  permis in SQLite
  functioneaza in Postgres daca actiunile sunt specificate ca proceduri stocate
  MySQL nu suporta WHEN, evenimente UPDATE cu atribute,triggers multiple pe acelasi eveniment, inlantuire de triggere
  Oracle: nu e permisa ciclarea datorita erorii mutating table
**************************************************************/

create table T1(A int);
create table T2(A int);
create table T3(A int);
create table T4(A int);

/**************************************************************
  SELF-TRIGGERING
  nu e permis in Oracle
**************************************************************/
drop trigger R1;
create trigger R1
after insert on T1
for each row
begin
  insert into T1 values (New.A+1);
end;

insert into T1 values (1);
select * from T1;

pragma recursive_triggers = on;

insert into T1 values (1);

delete from T1;
drop trigger R1;

create trigger R1
after insert on T1
for each row
when (select count(*) from T1) < 10
begin
  insert into T1 values (New.A+1);
end;

insert into T1 values (1);
select * from T1;

/**************************************************************
  ciclare
**************************************************************/

delete from T1;
drop trigger R1;
pragma recursive_triggers = off;

create trigger R1
after insert on T1
for each row
begin
  insert into T2 values (New.A+1);
end;

create trigger R2
after insert on T2
for each row
begin
  insert into T3 values (New.A+1);
end;

create trigger R3
after insert on T3
for each row
begin
  insert into T1 values (New.A+1);
end;

insert into T1 values (1);
select * from T1;
select * from T2;
select * from T3;

pragma recursive_triggers = on;

delete from T1;
delete from T2;
delete from T3;

drop trigger R3;

create trigger R3
after insert on T3
for each row
when (select count(*) from T1) < 100
begin
  insert into T1 values (New.A+1);
end;

insert into T1 values (1);
select * from T1;
select * from T2;
select * from T3;

/**************************************************************
  triggere conflictuale
**************************************************************/

drop trigger R1;
drop trigger R2;
drop trigger R3;
delete from T1;
delete from T2;
delete from T3;

create trigger R1
after insert on T1
for each row
begin
  update T1 set A = 2;
end;

create trigger R2
after insert on T1
for each row
when exists (select * from T1 where A = 2)
begin
  update T1 set A = 3;
end;

insert into T1 values (1);
select * from T1;

drop trigger R1;
drop trigger R2;
delete from T1;

create trigger R2
after insert on T1
for each row
when exists (select * from T1 where A = 2)
begin
  update T1 set A = 3;
end;

create trigger R1
after insert on T1
for each row
begin
  update T1 set A = 2;
end;

insert into T1 values (1);
select * from T1;

/**************************************************************
  invocari imbricate
**************************************************************/

drop trigger R1;
drop trigger R2;
delete from T1;

create trigger R1
after insert on T1
for each row
begin
  insert into T2 values (1);
  insert into T3 values (1);
end;

create trigger R2
after insert on T2
for each row
begin
  insert into T3 values (2);
  insert into T4 values (2);
end;

create trigger R3
after insert on T3
for each row
begin
  insert into T4 values (3);
end;

insert into T1 values (0);
select * from T1;
select * from T2;
select * from T3;
select * from T4;

/**************************************************************
  ROW-LEVEL IMMEDIATE ACTIVATION
  SQLite and MySQL non-standard
**************************************************************/

drop trigger R1;
drop trigger R2;
drop trigger R3;
delete from T1;
drop table T2;
create table T2 (a float);

insert into T1 values (1);
insert into T1 values (1);
insert into T1 values (1);
insert into T1 values (1);

create trigger R1
after insert on T1
for each row
begin
  insert into T2 select avg(A) from T1;
end;

insert into T1 select A+1 from T1;
select * from T1;
select * from T2;

/**************************************************************
  CLEANUP
**************************************************************/

delete from T1;
delete from T2;
delete from T3;
delete from T4;

drop table T1;
drop table T2;
drop table T3;
drop table T4;
