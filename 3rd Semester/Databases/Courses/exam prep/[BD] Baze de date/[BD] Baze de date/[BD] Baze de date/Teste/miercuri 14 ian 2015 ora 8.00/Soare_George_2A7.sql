--Pentru grupul 3 de tabele
--Soare George 2A7

--1

select nume,suma
from (
    select nume,(salariu*ore) as suma
    from angajati a, pontaje p
    where p.coda = a.coda 
    order by suma desc) 
where rownum=1;
--0.5 p
--vaianta corecta, se vad diferente clare !
select nume, sum(salariu*ore) as venit
from angajati a inner join pontaje p on a.coda = p.coda
group by nume
having sum(salariu*ore)=
  (select max(sum(salariu*ore))
  from angajati a inner join pontaje p on a.coda = p.coda
  group by a.coda);


--2

select den,nr
from(
    select d.den,count(coda)as nr
    from angajati a,departamente d
    where d.codd = a.codd
    group by d.den
    order by nr desc)
where rownum < 3;
--3 p


--3

select  a1.nume, a1.salariu, a1.codd, avg(a2.salariu) as avg_sal
from   angajati a1, angajati a2
where     a2.codd = a1.codd
group by a1.nume, a1.salariu, a1.codd
having  a1.salariu > avg(a2.salariu);
--3 p


--4

alter table angajati
add data_angajarii date default sysdate;

select * from angajati;
-- 3p


--5

update angajati a
set a.data_angajarii=(
              select p.data
              from pontaje p
              where a.coda=p.coda and rownum=1)
where a.coda in (select coda from pontaje);

rollback;

alter table angajati
drop column data_angajarii;
--1 p
--varianta corecta:
update angajati
set data_angajarii = 
  (select min(data)
  from pontaje p 
  where p.coda = angajati.coda)
where 
  (select min(data)
  from pontaje p
  where p.coda = angajati.coda) is not null;
/
select * from angajati;
/
rollback;
/
select * from angajati;

total:10.5