drop table Universitate cascade constraints;
drop table Student cascade constraints;
drop table Aplica cascade constraints;


create table Universitate(uNume varchar(20), oras varchar(20), inscrieri int);
create table Student(sID int, sNume varchar(20), medie real, dimLiceu int);
create table Aplica(sID int, uNume varchar(20), specializare varchar(20), decizie char(2));

delete from Student;
delete from Universitate;
delete from Aplica;

insert into Student values (123, 'Ioana', 9.90, 1000);
insert into Student values (234, 'Bogdan', 9.66, 1500);
insert into Student values (345, 'Cristian', 9.50, 500);
insert into Student values (456, 'Dorina', 9.90, 1000);
insert into Student values (567, 'Eduard', 7.90, 2000);
insert into Student values (678, 'Florin', 9.80, 200);
insert into Student values (789, 'George', 9.40, 800);
insert into Student values (987, 'Elena', 9.70, 800);
insert into Student values (876, 'Irina', 9.90, 400);
insert into Student values (765, 'Ioan', 7.90, 1500);
insert into Student values (654, 'Ioana', 9.90, 1000);
insert into Student values (543, 'Cristian', 9.40, 2000);

insert into Universitate values ('Cuza', 'Iasi', 15000);
insert into Universitate values ('Petre Andrei', 'Iasi', 36000);
insert into Universitate values ('Spiru Haret', 'Bucuresti', 10000);
insert into Universitate values ('Babes-Bolyai', 'Cluj', 21000);

insert into Aplica values (123, 'Cuza', 'Informatica', 'DA');
insert into Aplica values (123, 'Cuza', 'Fizica', 'NU');
insert into Aplica values (123, 'Petre Andrei', 'Informatica', 'DA');
insert into Aplica values (123, 'Babes-Bolyai', 'Fizica', 'DA');
insert into Aplica values (234, 'Petre Andrei', 'Biologie', 'NU');
insert into Aplica values (345, 'Spiru Haret', 'Bioinginerie', 'DA');
insert into Aplica values (345, 'Babes-Bolyai', 'Bioinginerie', 'NU');
insert into Aplica values (345, 'Babes-Bolyai', 'Informatica', 'DA');
insert into Aplica values (345, 'Babes-Bolyai', 'Fizica', 'NU');
insert into Aplica values (678, 'Cuza', 'Istorie', 'DA');
insert into Aplica values (987, 'Cuza', 'Informatica', 'DA');
insert into Aplica values (987, 'Petre Andrei', 'Informatica', 'DA');
insert into Aplica values (876, 'Cuza', 'Informatica', 'NU');
insert into Aplica values (876, 'Spiru Haret', 'Biologie', 'DA');
insert into Aplica values (876, 'Spiru Haret', 'Biologie', 'NU');
insert into Aplica values (765, 'Cuza', 'Istorie', 'DA');
insert into Aplica values (765, 'Babes-Bolyai', 'Istorie', 'NU');
insert into Aplica values (765, 'Babes-Bolyai', 'Psihologie', 'DA');
insert into Aplica values (543, 'Spiru Haret', 'Informatica', 'NU');
