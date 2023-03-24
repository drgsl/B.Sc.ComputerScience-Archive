--grupul 2 de tabele / probleme Cosmin Tirpescu A7 Anul 2

--1
select c.nume,sum(i.suma)Cumulat 
from incasari i,contribuabili c,taxe t
where i.codc=c.cod and i.codt=t.cod
group by c.nume;
--nu, nu ai facut altceva decat niste joinuri ! nu am ce sa iti dau la punctul asta !!
--0 p

--2
select t.DEN
from incasari i, taxe t
where t.cod in (select cod from taxe)
      and t.cod = i.codt and i.suma < (select avg(suma) 
	  from taxe tax, incasari inc 
	  where tax.tip = t.tip);
--0.5 p    

--3
select den,Suma 
from(
    select t.den,
	sum(i.suma)Suma
    from incasari i,taxe t
    where i.codt=t.cod
    group by i.codt,t.den
    order by Suma desc) 
where rownum in (1,2,3);
--3 p

--4
SAVEPOINT SALVARE;
update incasari 
set suma=suma*0.1;
select suma from incasari;
ROLLBACK to SALVARE;
select suma from incasari;
--unde sunt taxele de tipul 2?? era o subinterogare aici !
--suma=suma*1.1 sau suma=suma+suma*0.1, nu cum ai pus tu !
--varianta corecta:
update incasari 
set suma = suma*1.1
where codt in 
  (select cod
  from taxe 
  where tip = 2);
--0.75 p, nu am cum sa iti dau mai mult



--5
alter table contribuabili
add (adresa varchar2(25) default 'iasi');
alter table contribuabili
drop column adresa;
--3 p

total:7.25