1.select nume from elev,prieten where elev.id=prieten.id1 and prieten.id2 in (select id from elev where upper(nume)='GABRIEL');

2.select a.nume,a.clasa,b.nume,b.clasa from elev a,elev b,place where a.id=place.id1 and b.id=place.id2 and a.clasa>=b.clasa+2;

---nu eu---
3.select a.nume,a.clasa,b.nume,b.clasa from elev a,elev b,place c,place d  where a.id=c.id1 and a.id=d.id2 and b.id=c.id2 and b.id=d.id1 and b.id<a.id;

4.select a.nume,a.clasa,b.nume,b.clasa,c.nume,c.clasa from elev a,elev b,elev c,place d,place e where a.id=d.id1 and b.id=d.id2 and b.id=e.id1 and c.id=e.id2 and a.id!=e.id2 ;

---nu eu---
5.SELECT distinct nume,clasa FRom ELEV,PLace MINUS SELECT distinct nume,clasa FRom ELEV,PLace WHERE id=id1 OR id=id2 order by clasa,nume;

6.select a.nume,a.clasa,b.nume,b.clasa from elev a,elev b,place where a.id=id1 and b.id=id2 and b.id not in (select id1 from place);

7.select nume,clasa from elev where (nume,clasa) not in (select unique a.nume,a.clasa from elev a,elev b,prieten where a.id=id1 and b.id=id2 and a.clasa<>b.clasa);

8.select nume,clasa from elev where (nume,clasa) not in (select unique a.nume,a.clasa from elev a,elev b,prieten where a.id=id1 and b.id=id2 and a.clasa=b.clasa)

--cu 2 randuri mai mult--
9.select unique a.nume,a.clasa,b.nume,b.clasa,c.nume,c.clasa
   from elev a, elev b, elev c,elev f,prieten d,prieten e, place
   where (a.id=d.id1 and b.id<>d.id2 and b.id<>a.id) and (a.id=place.id1 and b.id=place.id2 and b.id<>a.id) and 
   (a.id=d.id1 and b.id=e.id1 and c.id=d.id2 and f.id=e.id2 and c.id=f.id and b.id<>a.id);

---nu eu---
10.select count(id) - count(distinct nume) from elev;

11.select count(id1)/count(distinct id1) from prieten;

12.

13

14.

15.update elev set clasa=clasa+1;
   select nume,clasa from elev where clasa>12;

16.delete from elev where clasa>12;
	select count(id) from elev;

17.delete from prieten where id1 not in(select id from elev) and id2 not in (select id from elev);
delete from place where id1 not in(select id from elev) and id2 not in (select id from elev);
select distinct a.nume from elev a,elev b,place,prieten where ((a.id=prieten.id1 and prieten.id2=b.id and upper(b.nume)='AUSTIN') or (a.id=prieten.id2 and prieten.id1=b.id and upper(b.nume)='AUSTIN')) or (a.id=place.id2 and place.id1=b.id and upper(b.nume)='AUSTIN');

18.insert into prieten (select unique a.id,c.id from elev a,elev b,elev c,prieten d,prieten e where a.id=d.id1 and b.id=d.id2 and b.id=e.id1 and c.id=e.id2 and a.id<>c.id );
select a.nume from elev a,elev b,prieten where a.id=id1 and b.id=id2 and upper(b.nume)='JORDAN';
