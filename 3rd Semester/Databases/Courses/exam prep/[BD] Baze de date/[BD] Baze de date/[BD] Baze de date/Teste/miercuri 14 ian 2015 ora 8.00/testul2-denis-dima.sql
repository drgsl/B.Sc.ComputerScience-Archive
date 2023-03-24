select * from contribuabili;
select * from taxe;
select * from incasari;

--1

SELECT contribuabili.nume,sum(incasari.suma) Suma
FROM incasari ,contribuabili ,taxe 
WHERE incasari.codc=contribuabili.cod and incasari.codt=taxe.cod
GROUP BY contribuabili.nume;
--nu ai facut decat niste joinuri ! 
--0.5 p
--varianta corecta (cred ca se observa diferentele):
select nume,sum(suma)valoare_cumulata
from contribuabili c inner join incasari i on c.cod=i.codc
group by nume
having sum(suma) = 
  (select max(sum(suma)) 
  from incasari 
  group by codc);


--3

SELECT den,Suma 
FROM(
    select taxe.den,sum(incasari.suma)Suma
    from incasari ,taxe 
    where incasari.codt=taxe.cod
    GROUP by incasari.codt,taxe.den
    order by Suma desc) 
WHERE rownum in (1,2,3);
--3 p

--4.

SAVEPOINT SavePo;
UPDATE incasari 
set suma=suma*0.1;--suma=suma* 1.1 sau suma = suma+suma*0.1 ! 
--0.25 p
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

total:6.75 