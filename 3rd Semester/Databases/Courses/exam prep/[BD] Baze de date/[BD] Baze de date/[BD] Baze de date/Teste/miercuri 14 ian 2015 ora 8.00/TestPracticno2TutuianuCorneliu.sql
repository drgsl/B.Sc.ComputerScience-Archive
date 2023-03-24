--grupul 2 probleme
--1
select nume,max(Cumulat) 
from (
select c.nume,sum(i.suma)Cumulat
from incasari i,contribuabili c,taxe t
where i.codc=c.cod and i.codt=t.cod
group by c.nume
order by Cumulat desc)  
group by nume;
--ai afisat prea multi !!!
--0.5 p
--varianta corecta:
select nume,sum(suma)valoare_cumulata
from contribuabili c inner join incasari i on c.cod=i.codc
group by nume
having sum(suma) = 
  (select max(sum(suma)) 
  from incasari 
  group by codc);

--2
select den,tip,suma
from taxe t,incasari i
where suma < (
select avg(i.suma)
from taxe t, incasari i
where i.codt=t.cod and tip=t.tip
group by t.tip)
;
--0 p

--3
select den,Suma 
from(
    select t.den,sum(i.suma)Suma
    from incasari i,taxe t
    where i.codt=t.cod
    group by i.codt,t.den
    order by Suma desc) 
where rownum in (1,2,3);
--3 p

--4.
SAVEPOINT SP1;
update incasari 
set suma=suma*0.1;

select suma 
from incasari;

rollback to SP1;

select suma 
from incasari;
--1 p
--suma = suma*1.1 !!!
--unde e where-ul?
--varianta corecta:
update incasari 
set suma = suma*1.1
where codt in 
  (select cod
  from taxe 
  where tip = 2);

--5
alter table contribuabili
add (adresa varchar2(25) default 'iasi');

alter table contribuabili
drop column adresa;
--3 p

total:7.5