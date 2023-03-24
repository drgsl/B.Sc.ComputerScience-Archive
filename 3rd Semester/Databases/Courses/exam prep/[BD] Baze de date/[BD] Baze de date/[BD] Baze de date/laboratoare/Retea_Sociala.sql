drop table Elev;
drop table Prieten;
drop table Place;

create table Elev(ID int, nume VARCHAR2(10), clasa int);
create table Prieten(ID1 int, ID2 int);
create table Place(ID1 int, ID2 int);

/* Populate the tables with our data */
insert into Elev values (1510, 'Jordan', 9);
insert into Elev values (1689, 'Gabriel', 9);
insert into Elev values (1381, 'Tiffany', 9);
insert into Elev values (1709, 'Cassandra', 9);
insert into Elev values (1101, 'Haley', 10);
insert into Elev values (1782, 'Andrew', 10);
insert into Elev values (1468, 'Kris', 10);
insert into Elev values (1641, 'Brittany', 10);
insert into Elev values (1247, 'Alexis', 11);
insert into Elev values (1316, 'Austin', 11);
insert into Elev values (1911, 'Gabriel', 11);
insert into Elev values (1501, 'Jessica', 11);
insert into Elev values (1304, 'Jordan', 12);
insert into Elev values (1025, 'John', 12);
insert into Elev values (1934, 'Kyle', 12);
insert into Elev values (1661, 'Logan', 12);

insert into Prieten values (1510, 1381);
insert into Prieten values (1510, 1689);
insert into Prieten values (1689, 1709);
insert into Prieten values (1381, 1247);
insert into Prieten values (1709, 1247);
insert into Prieten values (1689, 1782);
insert into Prieten values (1782, 1468);
insert into Prieten values (1782, 1316);
insert into Prieten values (1782, 1304);
insert into Prieten values (1468, 1101);
insert into Prieten values (1468, 1641);
insert into Prieten values (1101, 1641);
insert into Prieten values (1247, 1911);
insert into Prieten values (1247, 1501);
insert into Prieten values (1911, 1501);
insert into Prieten values (1501, 1934);
insert into Prieten values (1316, 1934);
insert into Prieten values (1934, 1304);
insert into Prieten values (1304, 1661);
insert into Prieten values (1661, 1025);
insert into Prieten select ID2, ID1 from Prieten;

insert into Place values(1689, 1709);
insert into Place values(1709, 1689);
insert into Place values(1782, 1709);
insert into Place values(1911, 1247);
insert into Place values(1247, 1468);
insert into Place values(1641, 1468);
insert into Place values(1316, 1304);
insert into Place values(1501, 1934);
insert into Place values(1934, 1501);
insert into Place values(1025, 1101);

create table Elev(ID int, nume VARCHAR2(10), clasa int);
create table Prieten(ID1 int, ID2 int);
create table Place(ID1 int, ID2 int);

--1.Afisati prietenii lui Gabriel
--varianta cu subinterogare, dar nu e tocmai indicata deoarece in tabela de elevi exista doi Gabrieli 
select nume,clasa
from elev e inner join prieten p on p.id1=e.id
where id2 in
  (select id
  from elev
  where nume='Gabriel')
order by nume,clasa
--
select e2.nume,e2.clasa
from elev e1 inner join prieten p on p.id1=e1.id inner join elev e2 on e2.id=p.id2 
where e1.nume='Gabriel' and e2.clasa=9
union
select e2.nume,e2.clasa
from elev e1 inner join prieten p on p.id1=e1.id inner join elev e2 on e2.id=p.id2 
where e1.nume='Gabriel' and e2.clasa=10
union
select e2.nume,e2.clasa
from elev e1 inner join prieten p on p.id1=e1.id inner join elev e2 on e2.id=p.id2 
where e1.nume='Gabriel' and e2.clasa=11
union
select e2.nume,e2.clasa
from elev e1 inner join prieten p on p.id1=e1.id inner join elev e2 on e2.id=p.id2 
where e1.nume='Gabriel' and e2.clasa=12
--
select e2.nume,e2.clasa
from elev e1 inner join prieten p on p.id1=e1.id inner join elev e2 on e2.id=p.id2 
where e1.nume='Gabriel' and e1.clasa=9
union
select e2.nume,e2.clasa
from elev e1 inner join prieten p on p.id1=e1.id inner join elev e2 on e2.id=p.id2 
where e1.nume='Gabriel' and e1.clasa=11

--2.Pentru fiecare elev care place pe un altul cu 2 sau mai mult de 2 clase mai putin decat a sa,
--afiºaþi numele ºi clasa sa, ºi numele si clasa elevului pe care il place.
select e1.nume,e1.clasa,e2.nume,e2.clasa
from elev e1 inner join place p on e1.id=p.id1 inner join elev e2 on e2.id=p.id2
where e1.clasa-e2.clasa>1

--3.Pentru fiecare pereche de elevi care se plac reciproc, returnaþi numele ºi clasa ambilor. Fiecare pereche sa aparã o singurã datã.
select e1.nume,e1.clasa,e2.nume,e2.clasa
from elev e1 inner join place p on e1.id=p.id1 inner join elev e2 on e2.id=p.id2
intersect
select e1.nume,e1.clasa,e2.nume,e2.clasa
from elev e2 inner join place p on e2.id=p.id1 inner join elev e1 on e1.id=p.id2
where e1.nume<e2.nume
--
select e1.nume,e1.clasa,e2.nume,e2.clasa
from elev e1,elev e2 
where (e1.id,e2.id)in
  (select t.id1,t.id2 from
    (select p1.id1,p1.id2,lag(p1.id2,1,0)over(order by p1.rowid)as id2_prev
    from place p1 inner join place p2 on p1.id1=p2.id2 and p1.id2=p2.id1)t
    where id1<>id2_prev)

--4.Pentru fiecare situaþie în care elevul A îl place pe B, dar elevul B îl place pe un alt elev C, returnaþi numele ºi clasa pentru A,B,C
select e1.nume,e1.clasa,e2.nume,e2.clasa,e3.nume,e3.clasa
from elev e1,elev e2,elev e3,place a,place b,place c
where e1.id=a.id1 and e2.id=a.id2 and e1.id<>b.id2 and e2.id=b.id1 and e2.id=c.id1 and e3.id=c.id2

--5.Gãsiþi toþi elevii care nu apar în tabela Place (nu place ºi nu e plãcut) ºi returnaþi numele ºi clasa lor. Sortaþi dupã clasã apoi dupã nume.
select nume,clasa
from elev 
minus
select e1.nume,e1.clasa
from place p inner join elev e1 on e1.id=p.id1
minus
select e2.nume,e2.clasa
from place p inner join elev e2 on e2.id=p.id2
order by clasa,nume
--
select nume,clasa
from elev
where id not in 
  (select id1
  from place)
and id not in
  (select id2
  from place)
order by clasa  

--6. Pentru fiecare situaþie în care A îl place pe B dar B nu place pe nimeni, returnaþi numele ºi clasa lui A ºi B.
select e1.nume,e1.clasa,e2.nume,e2.clasa
from elev e1 inner join place p on e1.id=p.id1 inner join elev e2 on e2.id=p.id2
where e2.id not in
  (select id1
  from place) 
  
--7. Gãsiþi numele ºi clasa pentru elevii care au prieteni doar în clasa lor. Returnaþi rezultatul sortat dupã clasã apoi dupã nume.  
--se selecteaza mai intai toate perechile de prieteni din clasa diferite
--apoi se tine cont ca relatia de prietenie e in ambele sensuri
select nume,clasa
from elev 
where id not in
  (select e1.id
  from elev e1 inner join prieten p on e1.id=p.id1 inner join elev e2 on e2.id=p.id2
  where e1.clasa<>e2.clasa)
and id not in
  (select e2.id
  from elev e1 inner join prieten p on e1.id=p.id1 inner join elev e2 on e2.id=p.id2
  where e1.clasa<>e2.clasa)
order by nume,clasa 

--8.Gãsiþi numele ºi clasa elevilor care au doar prieteni în alte clase.
select nume,clasa
from elev 
where id not in
  (select e1.id
  from elev e1 inner join prieten p on e1.id=p.id1 inner join elev e2 on e2.id=p.id2
  where e1.clasa=e2.clasa)
and id not in
  (select e2.id
  from elev e1 inner join prieten p on e1.id=p.id1 inner join elev e2 on e2.id=p.id2
  where e1.clasa=e2.clasa)

--9.Pentru fiecare elev A care îl place pe B iar cei doi nu sunt prieteni, gãsiþi dacã au un prieten C în
--comun. Pentru aceste situaþii returnaþi numele ºi clasa elevilor (A,B,C).
select e1.nume,e1.clasa,e2.nume,e2.clasa
from elev e1 inner join place p on e1.id=p.id1 inner join elev e2 on e2.id=p.id2
--se selecteaza mai intai toate perechile de prieteni cu reuniune
where (id1,id2)not in
  (select id1,id2
  from prieten
  union
  select id2,id1
  from prieten)
--verifica daca au prieteni in comun
and exists 
  (select a.id2 
  from prieten a inner join prieten b on a.id2=b.id1
  where ((p.id1=a.id1 and p.id2=b.id2)or(p.id1=b.id2 and p.id2=a.id1)))

--10.Gãsiþi diferenþa dintre numãrul de elevi din ºcoalã si numãrul de nume diferite.
select count(id)-count(distinct nume)diferenta
from elev

--11.Care este numarul mediu de prieteni pe elev?
select avg(count(p.id2))medie_prieteni
from elev e inner join prieten p on p.id2=e.id
group by e.id

--12.Gãsiþi numãrul de elevi care sunt prieteni cu Cassandra sau sunt prieteni ai prietenilor
--Cassandrei. Nu o numãraþi ºi pe Cassandra chiar dacã tehnic este prietenã cu prietenii Cassandrei.
select count(e.id)
from elev e inner join prieten p1 on e.id=p1.id1 inner join prieten p2 on p1.id2=p2.id1
where e.nume='Cassandra'

--13. Gãsiþi elevii ºi clasa tuturor elevilor care sunt plãcuþi de mai mult de un elev.
select e2.nume,e2.clasa
from elev e1 inner join place p on e1.id=p.id1 inner join elev e2 on e2.id=p.id2
group by e2.nume,e2.clasa
having count(p.id1)>1

--14.Gãsiþi numele ºi clasa studentului/ilor cu cel mai mare numãr de prieteni.
select e1.nume,e1.clasa
from elev e1 inner join prieten p on e1.id=p.id1 inner join elev e2 on e2.id=p.id2
group by e1.nume,e1.clasa
having count(p.id1)=
  (select max(count(p.id2))
  from prieten p inner join elev e2 on e2.id=p.id2
  group by p.id2)
--
select e1.nume,e1.clasa
from elev e1 inner join prieten p on e1.id=p.id1 inner join elev e2 on e2.id=p.id2
group by e1.nume,e1.clasa
having count(p.id1)=
  (select max(count(p.id2))
  from prieten p
  group by p.id2)
 
