drop table curs_student
drop table curs_profesor
drop table student
drop table profesor
drop table grad
drop table curs

create table curs(
  idcurs number(2)
    constraint pk_curs primary key
    constraint nn_curs not null,
  denumire varchar2(30));  

create table grad(
  idgrad number(1)
    constraint pk_idgrad primary key
    constraint nn_idgrad not null,
  titlu varchar2(25),  
    constraint ck_titlu check(titlu=ltrim(initcap(titlu))),
  salariu varchar2(15)
    constraint ck_salariu check(salariu < 10000),
  avans varchar2(15));  
     
create table profesor(
  idprofesor number(2)
    constraint pk_profesor primary key
    constraint nn_profesor not null,
  numeprenume varchar2(50)
    constraint nn_personal_numeprenume not null
    constraint ck_personal_numeprenume check(numeprenume=LTRIM(INITCAP(numeprenume))),
  catedra varchar2(30),
  idgrad number(1)
    constraint fk_idgrad references grad(idgrad));
    
create table student(
  nrmatricol varchar2(20)
    constraint pk_nrmatricol primary key
    constraint nn_nrmatricol not null,
  numeprenume varchar2(50)
    constraint nn_personal_numeprenume_s not null
    constraint ck_personal_numeprenume_s check(numeprenume=LTRIM(INITCAP(numeprenume))),
  grupa varchar2(7));  

create table curs_profesor(
  idcurs number(2)
    constraint fk_idcurs references curs(idcurs),
  idprofesor number(2)
    constraint fk_idprofesor references profesor(idprofesor),
  ziua date
    default sysdate
    constraint ck_ziua check(ziua>=to_date('01/10/2014','DD/MM/YYYY') and ziua<=to_date('01/06/2015','DD/MM/YYYY')),
  ora varchar2(5),
  sala varchar2(5) 
    default 'C2'
    constraint ck_sala check (sala in('C1','C309','C112','C401','C402','C403','C409','C412')),
  constraint pk_curs_profesor primary key(idcurs,idprofesor));

create table curs_student(
  idcurs number(2)
    constraint fk_idcurs_s references curs(idcurs),
  nrmatricol varchar2(20)
    constraint fk_nrmatricol references student(nrmatricol),
  nota varchar2(4)
    constraint ck_nota check(nota>=5),
  constraint pk_curs_student primary key(idcurs,nrmatricol));  

insert into curs values (1,'Baze de Date');
insert into curs values (2, 'Probabilitati si Statistica');
 
insert into grad values (1,'Profesor',6000,2500);
insert into grad values (2,'Conferentiar',2500,1000);
insert into grad values (3,'Lector',1800,8000);
insert into grad values (4,'Asistent',1400,600);
insert into grad values (5,'Colaborator',1200,500);

insert into profesor values (1,'Ionescu Mihai','Sisteme Distribuite',2);
insert into profesor values (2,'Toma Marius','Optimizare',4);

insert into student values (1,'Vasilescu Robert','IIA6');
insert into student values (2,'Popa Gigi','IIIB7');

insert into curs_profesor values (1,1,'07-OCT-2014','8.00','C112');
insert into curs_profesor values (2,2,'08-OCT-2014','12.00','');

insert into curs_student values (1,1,8);

--1.Creati copii ale tabelelor
create table copie_curs as select * from curs
create table copie_grad as select * from grad
create table copie_profesor as select * from profesor
create table copie_student as select * from student
create table copie_curs_profesor as select * from curs_profesor
create table copie_curs_student as select * from curs_student

--2.Sa se modifice table copie_profesor astfel incat sa se adauge campurile noi, data_angajare si data_nastere
alter table copie_profesor add(data_angajare date);
alter table copie_profesor add(data_nastere date);

--3.Stergeti campul data_nastere din tabela copie_profesor
alter table copie_profesor
drop column data_nastere

--3.Modificati table copie_student pentru a permite nume mai lungi in coloana numeprenume
alter table copie_student modify(numeprenume varchar2(55));

--4.Sa se redenumeasca coloana nrmatricol in codstudent
alter table copie_student 
rename column nrmatricol to codstudent

--5.Sa se redenumeasca tabela copie_grad in grad_didactic
rename copie_grad to grad_didactic

--6.Confirmati constrangerile adaugate interogand tabela user_constraints
select * from user_constraints



  