

CREATE TABLE Animal (
	IDAnimal int NOT NULL,
	IDAngajat int NOT NULL,
	Specie varchar2(25) NOT NULL,
	Nume varchar2(25) DEFAULT 'NoName',
	Sex char(1) NOT NULL,
	Culoare varchar2(25) DEFAULT 'Mixt',
	NrIncapere int NOT NULL,
	PRIMARY KEY(IDAnimal)
);

CREATE TABLE Tip_Animal (
	Specie varchar2(25) NOT NULL,
	SperantaViata int,
	TipBlana varchar2(25),
	Mancare varchar2(25) DEFAULT 'Orice',
	PRIMARY KEY(Specie)
);

CREATE TABLE Angajat (
	IDAngajat int NOT NULL,
	Nume varchar2(25) NOT NULL,
	Prenume varchar2(25) NOT NULL,
	DataAngajarii date NOT NULL,
	NrTelefon varchar2(15),
	Salariu varchar2(10) NOT NULL,
	NrAnimale int DEFAULT 0,
	PRIMARY KEY(IDAngajat)
);

CREATE TABLE FisaMedicala (
	IDFisa int NOT NULL,
	StareSanatate varchar2(25) DEFAULT 'Sanatos',
	DataUltimControl date NOT NULL,
	Sterilizare char(2),
	PRIMARY KEY(IDFisa)
);

CREATE TABLE Boli (
	IDTratament int NOT NULL,
	IDFisa int NOT NULL,
	Boala varchar2(25) NOT NULL,
	Tratament varchar2(25),
	PRIMARY KEY(IDTratament)
);

CREATE TABLE FisaAnimal (
	IDAnimal int NOT NULL,
	IDFisa int NOT NULL,
	PRIMARY KEY(IDFisa,IDAnimal)
);

ALTER TABLE Animal ADD CONSTRAINT Ref_Animal_to_Tip_Animal FOREIGN KEY (Specie)
	REFERENCES Tip_Animal(Specie);

ALTER TABLE Animal ADD CONSTRAINT Ref_Animal_to_Angajat FOREIGN KEY (IDAngajat)
	REFERENCES Angajat(IDAngajat);

ALTER TABLE Boli ADD CONSTRAINT Ref_Boli_to_FisaMedicala FOREIGN KEY (IDFisa)
	REFERENCES FisaMedicala(IDFisa);

ALTER TABLE FisaAnimal ADD CONSTRAINT Ref_FisaAnimal_to_Animal FOREIGN KEY (IDAnimal)
	REFERENCES Animal(IDAnimal);

ALTER TABLE FisaAnimal ADD CONSTRAINT Ref_FisaAnimal_to_FisaMedicala FOREIGN KEY (IDFisa)
	REFERENCES FisaMedicala(IDFisa);


CREATE or REPLACE TRIGGER adauga_boala AFTER INSERT ON Boli
FOR EACH ROW
BEGIN
UPDATE FisaMedicala
SET StareSanatate = 'Bolnav'
WHERE IDFisa = :new.IDFisa;
END;
/

INSERT INTO Angajat VALUES (235,'Vasile','Nustiu',to_date('2007-03-14','yyyy-mm-dd'),0484545131,2000,1);
INSERT INTO Angajat VALUES (214,'Ion','Stiu',to_date('2010-07-14','yyyy-mm-dd'),0477431,3000,1);
INSERT INTO Angajat VALUES (1,'Mada','Boca',to_date('2010-01-20','yyyy-mm-dd'),0744000001,1000,1); 
INSERT INTO Angajat VALUES (2,'Mihai','Popescu',to_date('2010-02-20','yyyy-mm-dd'),0744000002,1010,1); 
INSERT INTO Angajat VALUES (3,'Dumitru','Vascan',to_date('2010-05-25','yyyy-mm-dd'),0744000003,1030,1); 
INSERT INTO Angajat VALUES (4,'Denis','Dima',to_date('2011-02-12','yyyy-mm-dd'),0744000004,2000,1); 
INSERT INTO Angajat VALUES (5,'Adelina','Ichim',to_date('2011-05-10','yyyy-mm-dd'),0744000005,2050,1); 
INSERT INTO Angajat VALUES (6,'Norbert','Ionita',to_date('2012-07-15','yyyy-mm-dd'),0744000006,1550,1); 

INSERT INTO Tip_Animal VALUES('pisica',15,'scurta','peste');
INSERT INTO Tip_Animal VALUES('caine',10,'lunga','carne');;
INSERT INTO Tip_Animal (Specie)	VALUES ('altceva');

INSERT INTO Animal VALUES (125,235,'pisica','cat','M','maro',25);
INSERT INTO Animal VALUES (110,214,'caine','dog','M','negru',20);
INSERT INTO Animal VALUES (1,1,'pisica','Pisi','F','maro',1);
INSERT INTO Animal VALUES (2,2,'pisica','Cat','F','alb',1);
INSERT INTO Animal VALUES (3,3,'pisica','Tom','M','negru',1);
INSERT INTO Animal VALUES (4,4,'caine','Cutu','M','alb',2);
INSERT INTO Animal VALUES (5,5,'caine','Rex','M','negru',2);
INSERT INTO Animal VALUES (6,6,'caine','Bobica','F','gri',2);
INSERT INTO Animal VALUES (7,6,'altceva','Pufi','M','negru',3);

INSERT INTO FisaMedicala VALUES (12,'bolnav',to_date('2009-03-14','yyyy-mm-dd'),'da');
INSERT INTO FisaMedicala VALUES (10,NULL,to_date('2009-03-14','yyyy-mm-dd'),'da');
Insert into FisaMedicala (IDFisa, DataUltimControl, Sterilizare)
			VALUES (1, to_date('2011-03-14','yyyy-mm-dd'), 'da');
Insert into FisaMedicala (IDFisa, DataUltimControl, Sterilizare)
			VALUES (2, to_date('2011-03-15','yyyy-mm-dd'), 'nu');
Insert into FisaMedicala (IDFisa, DataUltimControl, Sterilizare)
			VALUES (3, to_date('2011-03-16','yyyy-mm-dd'), 'da');
Insert into FisaMedicala (IDFisa, DataUltimControl, Sterilizare)
			VALUES (4, to_date('2011-03-17','yyyy-mm-dd'), 'nu');
Insert into FisaMedicala (IDFisa, DataUltimControl, Sterilizare)
			VALUES (5, to_date('2011-03-18','yyyy-mm-dd'), 'da');
Insert into FisaMedicala (IDFisa, DataUltimControl, Sterilizare)
			VALUES (6, to_date('2011-03-19','yyyy-mm-dd'), 'da');	

INSERT INTO Boli VALUES (5,12,'raceala','CeaiSiCaldura');
INSERT INTO Boli VALUES (6,10,'raceala','CeaiSiCaldura');
INSERT INTO Boli VALUES (1,1,'raceala','CeaiSiCaldura');
INSERT INTO Boli VALUES (2,2,'raceala','CeaiSiCaldura');
INSERT INTO Boli VALUES (3,3,'raceala','CeaiSiCaldura');
INSERT INTO Boli VALUES (4,3,'chist','operatie');

INSERT INTO FisaAnimal VALUES (125,12);
INSERT INTO FisaAnimal VALUES (110,10);
INSERT INTO FisaAnimal VALUES (1,1);
INSERT INTO FisaAnimal VALUES (2,2);
INSERT INTO FisaAnimal VALUES (3,3);
INSERT INTO FisaAnimal VALUES (4,4);
INSERT INTO FisaAnimal VALUES (5,5);
INSERT INTO FisaAnimal VALUES (6,6);