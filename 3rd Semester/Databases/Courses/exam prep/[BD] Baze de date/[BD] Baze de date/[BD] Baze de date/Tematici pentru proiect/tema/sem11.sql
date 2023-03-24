1.
SELECT nume 
FROM elev 
WHERE id in (SELECT id2 FROM prieten WHERE id1 in (SELECT id FROM elev WHERE nume='Gabriel'));

2.
select distinct a.nume,a.clasa,b.nume,b.clasa 
from elev a,elev b,place 
where ABS(a.clasa-b.clasa)>=2 and a.id=id1 and b.id=id2 ;

3.
SELECT distinct a.nume,a.clasa,b.nume,b.clasa
from elev a,elev b,place c,place d
where a.id=c.id1 and b.id=c.id2 and c.id1=d.id2 and c.id2=d.id1 and a.id>b.id;

4.
SELECT distinct a.nume,a.clasa,b.nume,b.clasa,e.nume,e.clasa
from elev a,elev b,elev e,place c,place d
where a.id=c.id1 and b.id=c.id2 and c.id1<>d.id2 and c.id2=d.id1 and e.id=d.id2;

5.
SELECT e.nume, e.clasa
FROM Elev e
WHERE e.id NOT IN (SELECT id1
				   FROM Place)
AND e.id NOT IN (SELECT id2
				   FROM Place)
ORDER BY e.clasa, e.nume;
