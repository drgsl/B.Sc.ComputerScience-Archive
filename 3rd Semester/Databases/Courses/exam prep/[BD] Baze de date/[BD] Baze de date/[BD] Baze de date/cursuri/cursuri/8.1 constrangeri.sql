/**************************************************************
  Constrangeri: NON-NULL, cheie, bazate pe atribut si pe uplu, asertiuni
  SQLite, Postgres, Oracle: 
    nu permit constrangeri de tip CHECK cu subinterogari 
    nu implementeaza asertiunile
  MySQL: 
     permite declararea de constrangeri CHECK dar nu le verifica; 
     nu implementeaza asertiunile
**************************************************************/

/**************************************************************
  NON-NULL CONSTRAINTS
  medie nu trebuie sa ia valorbe NULL
**************************************************************/
drop table Student cascade constraints;
create table Student(sID int, sNume varchar(20), medie real not null, dimLiceu int);

insert into Student values (123, 'Ioana', 9.66, 1000);
insert into Student values (234, 'Alex', 9.33, null);
insert into Student values (345, 'Cristian', null, 500);
update Student set medie = null where sID = 123;
update Student set medie = null where sID = 456;
select * from student;

drop table Student;

/**************************************************************
  PRIMARY KEYS
  ID-urile sudentilor sunt unice
**************************************************************/

create table Student(sID int primary key, sNume varchar(20), medie real, dimLiceu int);

insert into Student values (123, 'Ioana', 9.66, 1000);
insert into Student values (234, 'Alex', 9.33, 1500);

insert into Student values (123, 'Cristian', 9.00, 500);

insert into Student values (null, 'Adina', 9.00, 500);

select * from student;

update Student set sID = 123 where sNume = 'Alex';
update Student set sID = sID - 111;
update Student set sID = sID + 111;

drop table Student;

/**************************************************************
  numai o cheie primara e permisa
**************************************************************/

create table Student(sID int primary key, sNume varchar(20) primary key,
                     medie real, dimLiceu int);


/**************************************************************
  dar orice numar de chei candidat
**************************************************************/
drop table student;
create table Student(sID int primary key, sNume varchar(20) unique,
                     medie real, dimLiceu int unique);

insert into Student values (123, 'Ioana', 9.66, 1000);
insert into Student values (234, 'Alex', 9.33, 1500);
insert into Student values (345, 'Ioana', 9.00, 500);
insert into Student values (456, 'Daria', 9.66, 1000);
insert into Student values (567, 'Ioana', 9.80, 1500);

insert into Student values(57, null, 9.80, 0);

drop table Student;


/**************************************************************
 chei multi-atribut
**************************************************************/
drop table Universitate cascade constraints;
create table Universitate(uNume varchar(20), oras varchar(20), inscrieri int,
                     primary key (uNume,oras));

insert into Universitate values ('Spiru Haret', 'Iasi', 10000);
insert into Universitate values ('Spiru Haret', 'Bucuresti', 5000);

insert into Universitate values ('Spiru Haret', 'Iasi', 2000);

insert into Universitate values ('Cuza', null, 2000);

drop table Universitate;


/**************************************************************
  chei multi-atribut
 restrictii semantice: 
  studentii pot aplica la fiecare universitate o singura data
  studentii pot aplica la fiecare specializare o singura data
**************************************************************/
drop table Aplica;

create table Aplica(sID int, uNume varchar(20), specializare varchar(20), decizie char(2),
                   unique(sID,uNume), unique(sID,specializare));
select * from Aplica;

insert into Aplica values (123, 'Cuza', 'Informatica', null);
insert into Aplica values (123, 'Asachi', 'Fizica', null);
insert into Aplica values (123, 'Cuza', 'Biologie', null);
insert into Aplica values (234, 'Cuza', 'Biologie', null);
insert into Aplica values (123, 'Spiru Haret', 'Fizica', null);
insert into Aplica values (123, 'Spiru Haret', 'Biologie', null);
select * from Aplica;
update Aplica set specializare = 'Informatica' where uNume = 'Spiru Haret';
insert into Aplica values (123, null, null, 'DA');
insert into Aplica values (123, null, null, 'NU');
insert into Aplica values (null, null, null, 'NU');

select * from Aplica;
drop table Aplica;


/**************************************************************
  constrangeri bazate pe atribute
  medie si dimLiceu sunt in interval
**************************************************************/
drop table Student;
create table Student(sID int, sNume varchar(20),
                     medie real check(medie <= 10.0 and medie >= 5.0),
                     dimLiceu int check(dimLiceu < 5000));

insert into Student values (123, 'Ioana', 9.66, 1000);
insert into Student values (234, 'Alex', 8.6, 1500);
update Student set dimLiceu = 4*dimLiceu where dimLiceu=1000;
select * from student;
select * from user_constraints where table_name = 'STUDENT';

drop table Student;

/**************************************************************
  constrangeri bazate pe tuple
  Cuza nu admite pe nimeni la Informatica
**************************************************************/
drop table Aplica;
create table Aplica(sID int, uNume varchar(20), specializare varchar(20), decizie char(2),
                   check(decizie = 'NU' or uNume <> 'Cuza'
                         or specializare <> 'Informatica'));

insert into Aplica values (123, 'Cuza', 'Informatica', 'NU');
insert into Aplica values (123, 'Spiru Haret', 'Informatica', 'DA');
insert into Aplica values (123, 'Cuza', 'Informatica', 'DA');
update Aplica set decizie = 'DA' where uNume = 'Cuza';
update Aplica set uNume = 'Cuza' where uNume = 'Spiru Haret';

drop table Aplica;

/**************************************************************
  not null cu check (in MySQL nu va fi verificata)
**************************************************************/

create table Student(sID int, sNume varchar(20),
                     medie real check(medie is not null), dimLiceu int);

insert into Student values (123, 'Ioana', null, 1000);

drop table Student;

/**************************************************************
  implementarea cheilor cu check - permisa in standard
  Tabel T(A), A este cheie
  SQLite, Postgres, Oracle: nu accepta
  MySQL: accepta dar nu verifica
**************************************************************/

create table T(A int check(A not in (select A from T)));

create table T(A int check((select count(distinct A) from T) =
                           (select count(*) from T)));

/**************************************************************
  subinterogari in check- permise in standard
  SQLite, Postgres, Oracle: nu accepta
  MySQL: accepta dar nu verifica
**************************************************************/

create table Student(sID int, sNume varchar(20), medie real, dimLiceu int);

create table Aplica(sID int, uNume varchar(20), specializare varchar(20), decizie varchar(20),
                   check(sID in (select sID from Student)));

create table Universitate(uNume varchar(20), oras varchar(20), inscrieri int,
                     check(inscrieri > (select max(dimLiceu) from Student)));

drop table Student;
drop table Aplica;
drop table Universitate;

/**************************************************************
 CONSTRÂNGERI REFERENTIALE (CHEI STRAINE)
  Postgres, Oracle: nu sunt necesare modificari
  SQLite: trebuie setat PRAGMA foreign_keys = ON si totul functioneaza
  MySQL: sunt necesare cateva modificari specificate unde e cazul
  
**************************************************************/

/**************************************************************
  DECLARAREA RESTRICTIILOR REFERENTIALE
  toate valorile sID si numele universitatilor din Aplica trebuie sa faca referire
  la studenti existenti si universitati existente
 *************************************************************/
drop table Universitate;
drop table Student;
drop table Aplica;
create table Universitate(uNume varchar(20) primary key, oras varchar(20), inscrieri int);

create table Student(sID int primary key, sNume varchar(20), medie real, dimLiceu int);

create table Aplica(sID int references Student(sID),
                   uNume varchar(20) references Universitate(uNume),
                   specializare varchar(20), decizie varchar(2));

/**************************************************************
  violari
  inserari sau actualizari in tabelul care referentiaza (Aplica)
  stergeri sau actualizari in tabelul referentiat (Student, Universitate)
  stergerea tabelelor referentiate (Student, Universitate)
**************************************************************/

insert into Aplica values (123, 'Cuza', 'Informatica', 'DA');
insert into Aplica values (234, 'Petre Andrei', 'Biologie', 'NU');

insert into Student values (123, 'Ioana', 9.80, 1000);
insert into Student values (234, 'Bogdan', 9.33, 1500);
insert into Universitate values ('Cuza', 'Iasi', 15000);
insert into Universitate values ('Petre Andrei', 'Iasi', 36000);
insert into Aplica values (123, 'Cuza', 'Informatica', 'DA');
insert into Aplica values (234, 'Petre Andrei', 'Biologie', 'NU');

update Aplica set sID = 345 where sID = 123;
update Aplica set sID = 234 where sID = 123;

delete from Universitate where uNume = 'Cuza';
delete from Student where sID = 234;
select * from Aplica;

delete from Student where sID = 123;

update Universitate set uNume = 'Petre-Andrei' where uNume = 'Petre Andrei';

drop table Student;

/**************************************************************
  optiunile CASCADE si SET NULL
  pentru stergeri si actualizari in tabelul referentiat (Student, Universitate)
  actualizarile nu sunt tratate in Oracle
**************************************************************/

drop table Aplica;
select * from Universitate;
create table Aplica(sID int references Student(sID) on delete set null,
                   uNume varchar(20) references Universitate(uNume) on delete cascade,-- on update cascade, --nu avem on update in Oracle
                   specializare varchar(20), decizie varchar(2));

insert into Student values (123, 'Ioana', 9.80, 1000);
insert into Student values (345, 'Cristian', 9.00, 500);

insert into Aplica values (123, 'Cuza', 'Informatica', 'DA');
insert into Aplica values (123, 'Petre Andrei', 'Informatica', 'DA');
insert into Aplica values (234, 'Petre Andrei', 'Biologie', 'NU');
insert into Aplica values (345, 'Cuza', 'Istorie', 'DA');
insert into Aplica values (345, 'Cuza', 'Informatica', 'DA');

select * from Aplica;
delete from Student where sID = 123;
delete from Universitate where uNume = 'Cuza';
select * from Aplica;

update Universitate set uNume = 'Petre-Andrei' where uNume = 'Petre Andrei';
select * from Aplica;


select * from user_constraints;
select * from user_constraints where upper(table_name)='APLICA';
alter table Aplica drop constraint where constraint_name in (select constraint_name from user_constraints where upper(table_name)='APLICA');

/**************************************************************
  restrictii intra-tabel, multi-atribut si optiunea CASCADE
**************************************************************/
drop table T;
create table T (A int, B int, C int, primary key (A,B),
                foreign key (B,C) references T(A,B) on delete cascade);
insert into T values (1,1,1);
insert into T values (2,1,1);
insert into T values (3,2,1);
insert into T values (4,3,2);
insert into T values (5,4,3);
insert into T values (6,5,4);
insert into T values (7,6,5);
insert into T values (8,7,6);


select * from T;
delete from T where A=1;
select * from T;

drop table Universitate;
drop table Student;
drop table Aplica;
drop table T;


/***********************************************************************************************************************
***************************************************************
  versiunea MYSQL
  necesita declararea cheilor straine separat de cea a atributelor
  necesita InnoDB storage engine,
  altfel accepta constrangerile dar nu le verifica
***************************************************************
**************************************************************/

/**************************************************************
  declarare
**************************************************************/

create table Universitate(uNume varchar(10) primary key, oras varchar(20), inscrieri int)
             engine = innodb;

create table Student(sID int primary key, sNume varchar(20), medie real, dimLiceu int)
             engine = innodb;

create table Aplica(sID int, uNume varchar(10), specializare varchar(20), decizie varchar(20),
                   foreign key (sID) references Student(sID),
                   foreign key (uNume) references Universitate(uNume)) engine = innodb;

/**************************************************************
  violari
**************************************************************/

insert into Aplica values (123, 'Cuza', 'Informatica', 'DA');
insert into Aplica values (234, 'Petre Andrei', 'Biologie', 'NU');

insert into Student values (123, 'Ioana', 9.80, 1000);
insert into Student values (234, 'Bogdan', 9.33, 1500);
insert into Universitate values ('Cuza', 'Iasi', 15000);
insert into Universitate values ('Petre Andrei', 'Iasi', 36000);
insert into Aplica values (123, 'Cuza', 'Informatica', 'DA');
insert into Aplica values (234, 'Petre Andrei', 'Biologie', 'NU');

update Aplica set sID = 345 where sID = 123;
update Aplica set sID = 234 where sID = 123;

delete from Universitate where uNume = 'Cuza';
delete from Student where sID = 234;
delete from Student where sID = 123;

update Universitate set uNume = 'Petre-Andrei' where uNume = 'Petre Andrei';

drop table Student;

/**************************************************************
  optiunile CASCADE si SET NULL
 *************************************************************/

drop table Aplica;

create table Aplica(sID int, uNume varchar(10), specializare varchar(20), decizie varchar(20),
                   foreign key (sID) references Student(sID) on delete set null,
                   foreign key (uNume) references Universitate(uNume) on update cascade)
                  engine = innodb;

insert into Student values (123, 'Ioana', 9.80, 1000);
insert into Student values (345, 'Cristian', 9.00, 500);

insert into Aplica values (123, 'Cuza', 'Informatica', 'DA');
insert into Aplica values (123, 'Petre Andrei', 'Informatica', 'DA');
insert into Aplica values (234, 'Petre Andrei', 'Biologie', 'NU');
insert into Aplica values (345, 'Cuza', 'Istorie', 'DA');
insert into Aplica values (345, 'Cuza', 'Informatica', 'DA');

select * from Aplica;
delete from Student where sID > 200;
select * from Aplica;

update Universitate set uNume = 'Petre-Andrei' where uNume = 'Petre Andrei';
select * from Aplica;

/*********************************************************************************************************************
  constrangeri intra-tabel, multi-atribut si CASCADE
**************************************************************/
drop table T;
create table T (A int, B int, C int, primary key (A,B),
                foreign key (B,C) references T(A,B)) on delete cascade);
insert into T values (1,1,1);
insert into T values (2,1,1);
insert into T values (3,2,1);
insert into T values (4,3,2);
insert into T values (5,4,3);
insert into T values (6,5,4);
insert into T values (7,6,5);
insert into T values (8,7,6);

delete from T where A=1;
select * from T;


/*****************************
declararea de constrangeri dupa ce avem date
**************************************************************************************/
drop table T;
create Table T(A int);
insert into T values(1);
insert into T values(1);
alter table T add constraint pk Primary key(A);
/*******************************************************************
regasirea constrangerilor in Oracle
************************************************************/
select * from user_constraints;
select * from user_constraints where upper(table_name)='T';


/*cleanup*/
drop table Aplica;
drop table Universitate;
drop table Student;
drop table T;

/*constrangeri dezactivate */
drop table Student;
create table Student(sID int CONSTRAINT pk primary key, sNume varchar(20), medie real, dimLiceu int);
ALTER TABLE Student
  DISABLE CONSTRAINT pk;
  
insert into Student values (123, 'Ioana', 9.66, 1000);
insert into Student values (123, 'Alex', 9.33, null);

ALTER TABLE Student
  ENABLE CONSTRAINT pk;

drop table exceptions;  
create table exceptions (row_id rowid, owner varchar2(30), table_name varchar2(30), constraint varchar2(30));
  
  ALTER TABLE Student ENABLE PRIMARY KEY EXCEPTIONS INTO EXCEPTIONS;

select * from exceptions;

SELECT * FROM Student, EXCEPTIONS
    WHERE EXCEPTIONS.constraint = 'PK'
    AND Student.rowid = EXCEPTIONS.row_id;
    