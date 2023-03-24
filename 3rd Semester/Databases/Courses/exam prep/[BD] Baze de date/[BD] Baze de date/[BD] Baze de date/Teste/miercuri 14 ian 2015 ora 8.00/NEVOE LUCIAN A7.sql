-- 1
select co.nume, i.sum(suma)
from CONTRIBUABILI co inner join INCASARI i ON co.cod=i.codc
where sum(suma)=
  (select max(sum(suma)) 
  from INCASARI
  group by co.COD);
--trebuia pus i.codc, in loc de co.cod ! in rest e ok !
--iti dau 2.5 p 
  
--2
select den, suma
from taxe inner join incasari on codt=cod
where suma<
  (select avg(suma)
  from incasari
  group by tip)
;
--0 p, nu asa se rezolva !
--varianta corecta:
select distinct t.tip, lpad(round((select avg(distinct suma) from incasari, taxe where codt = cod and tip = t.tip),2),7)medie_taxe, den, suma 
from taxe t inner join incasari i on t.cod = i.codt 
where suma < 
  (select avg(distinct suma) 
  from incasari, taxe
  where codt = cod and tip = t.tip);

--3
select den 
from taxe inner join incasari on codt=cod
where ROWNUM=3 AND sum(suma) in 
  (select sum(suma) 
  from incasari
  group by incasari.CODC);
  --0.5 p
--varianta corecta:
select * 
from(
  select den, sum(suma) as incasari
  from incasari i inner join taxe t on i.codt = t.cod
  group by den
  order by incasari desc)
where rownum < 4;
  
  
--4
update INCASARI inner join TAXE on codt=cod
SET suma=suma*1.1 
where cod=2;
select suma 
from INCASARI inner join TAXE on codt=cod
where cod=2;
ROLLBACK;
--nu e chiar corect ! tu ai pus cod = 2, dar de unde stii ca taxele de tipul 2 au codul 2 ?
--nu se pune join in update !
--1 p
update incasari 
set suma = suma*1.1
where codt in 
  (select cod
  from taxe 
  where tip = 2);


--5
ALTER TABLE CONTRIBUABILI 
ADD COLUMN ADRESA VARCHAR2(20) DEFAULT IASI ;  
ALTER TABLE CONTRIBUABILI
DROP COLUMN ADRESA;
--3 p

total:7 p