/*C4*/
/*cascade_constraints meaning daca sterg datele din parintele, se sterge automat si datele din copil*/
 
drop table CadruMedical cascade constraints;
drop table FisaMedicala cascade constraints;
drop table FisaPacient cascade constraints;
drop table Pacient cascade constraints;
drop table Boli cascade constraints;

create table CadruMedical(
IDCadruMedical int not null PRIMARY KEY,
Nume varchar2(20) not null,
Prenume varchar2(20) not null,
NrTelefon varchar2(20),
NrPacienti int
);

create table FisaMedicala(
IDFisa int not null PRIMARY KEY,
GrSanguina varchar2(5),
AntMedicale varchar(20) default 'Necunoscut'
);

create table Pacient(
IDPacient int not null PRIMARY KEY,
IDCadruMedical int not null,
Nume varchar2(30) default 'PersNecunoscuta',
Prenume varchar2(30) default 'PersNecunoscuta',
Varsta int,
Sex varchar2(5) not null,
Adresa varchar2(30) default 'Necunoscuta',
IDSalon int not null
);

create table FisaPacient(
IDFisa int not null,
IDPacient int not null
);

create table Boli(
IDTratament int not null PRIMARY KEY,
IDFisa int not null,
Boala varchar2(20) not null,
Tratament varchar2(20) not null,
Investigatii varchar2(20) not null,
Observatii varchar2(20) not null
);

select * from "FISAMEDICALA";
select * from "FISAPACIENT";
select * from BOLI;
select * from CADRUMEDICAL;
select * from PACIENT;

/*prin alter table am putut pune FK*/

alter table Pacient add FOREIGN KEY (IDCadruMedical) REFERENCES CadruMedical(IDCadruMedical);
alter table FisaPacient add FOREIGN KEY (IDPacient) REFERENCES Pacient(IDPacient);
alter table FisaPacient add FOREIGN KEY (IDFisa) REFERENCES FisaMedicala(IDFisa);
alter table Boli add FOREIGN KEY (IDFisa) REFERENCES FisaMedicala(IDFisa);

/*atunci cand facem update la tabela Boli automant in tabela FisaMedicala o sa puna la AntMedical = Inexistent pentru IDFisa dat la intrare*/
drop trigger adauga_boala;
CREATE TRIGGER adauga_boala AFTER UPDATE ON Boli
FOR EACH ROW
BEGIN
UPDATE FisaMedicala
SET AntMedicale = 'Inexistent'
WHERE IDFisa = :new.IDFisa;
END;


insert into CadruMedical values(123,'Badea','Stefan','0720561045',12);
insert into CadruMedical values(189,'Bunea','Andrei','0765356562',5);
insert into CadruMedical values(892,'Andreiescu','Tudor','0784532233',165);
insert into CadruMedical values(100,'Susan','Cosmin','0768952336',17);
insert into CadruMedical values(313,'Raduta','Laurentiu','0798104547',1);

insert into FisaMedicala values(982,'0','Cardiopatie');
insert into FisaMedicala values(650,'1','Gastrita');
insert into FisaMedicala values(345,'2','Durere Cap');
insert into FisaMedicala values(159,'3','Osteoporoza');
insert into FisaMedicala values(780,'0','Gastita');
insert into FisaMedicala (IDFisa,GrSanguina) values(870,'1');

insert into Pacient(IDPacient,IDCadruMedical,Varsta,Sex,Adresa,IDSalon) values(555,123,32,'M','Stefan cel Mare',15);
insert into Pacient(IDPacient,IDCadruMedical,Nume,Prenume,Varsta,Sex,IDSalon) values(32,189,'Zamfir','Mihai',12,'M',10);
insert into Pacient values(62,100,'Boboc','Florin',20,'M','Creta',60);
insert into Pacient values(45,313,'Castor','Cornelia',45,'F','Speranta',31);
insert into Pacient values(935,892,'Danca','Aurelia',100,'F','Crin',23);

insert into FisaPacient values(982,555);
insert into FisaPacient values(345,32);
insert into FisaPacient values(780,45);
insert into FisaPacient values(650,45);
insert into FisaPacient values(159,935);

insert into Boli values(1972,982,'Scolioza','Fizio','Analize','Dureri');
insert into Boli values(6258,345,'Raie','Vaccin','Anomalie','Mancarimi');
insert into Boli values(6912,159,'Durere de Cap','Pastile','Neurolog','Nici una');
insert into boli values(3123,650,'Strabism','Ochelari','Oftalmolog','Exercitii');
insert into Boli values(2331,780,'Salmonela','Sange','Diaree','Dureri de burta');

update Boli set TRATAMENT='Paracetamol' where IDFISA=650;
 
select * from "FISAMEDICALA";
select * from "FISAPACIENT";
select * from BOLI;
select * from CADRUMEDICAL;
select * from PACIENT;

/*C5*/

/*view inerent actualizat, creaza o noua tabela care afiseaza ce ii dai la intrare*/

drop view Detalii;
create view Detalii as select IDTratament,Boala,Observatii from Boli where IDFisa=982 or Observatii='Dureri de burta';

select * from Detalii;
select * from Boli;

delete from Detalii where IDTRATAMENT=2331;

select * from Detalii;
select * from Boli;

/*view si trigger creeaza o noua tabela si atunci cand se face un delete se actualizeaza tabela parinte*/

drop view Detalii;
create view Detalii as select IDTratament,Boala,Observatii from Boli where IDFisa=982 or Observatii='Dureri de burta';

select * from Detalii;
select * from Boli;

drop trigger DetaliiDelete;
create trigger DetaliiDelete instead of delete on Detalii
for each row
begin
delete from Boli
where IDTratament=:old.IDTratament;
end;

delete from Detalii where IDTRATAMENT=1972;

select * from Detalii;
select * from Boli;

/*C6*/
/*index pe functie, e folosita pentru rapiditate */
create index up on Boli(upper(Boala));
select * from Boli where upper(Boala) = 'STRABISM';

explain plan 
set statement_id = 'upper_username' for
select * from Boli where upper(Boala) = 'STRABISM';
SELECT PLAN_TABLE_OUTPUT FROM TABLE(DBMS_XPLAN.DISPLAY(NULL, 'upper_username','TYPICAL'));
