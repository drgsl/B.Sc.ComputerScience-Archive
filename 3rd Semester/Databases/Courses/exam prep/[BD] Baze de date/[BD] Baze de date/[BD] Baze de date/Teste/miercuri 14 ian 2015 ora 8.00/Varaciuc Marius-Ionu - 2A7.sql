--1--
SELECT nume,prenume,ns1.nota from studenti s  inner join note_studenti ns1 on ns1.mat=s.mat WHERE s.mat in (
  SELECT ns.mat from note_studenti ns GROUP BY ns.mat HAVING AVG(ns.nota) = (SELECT MAX(AVG(ns2.nota)) from note_studenti ns2 GROUP BY ns2.nota
  ));
  --3 p
  
--2--
SELECT s.mat, s.nume, s.prenume FROM studenti s WHERE s.mat in(
 SELECT ns.mat FROM note_studenti ns GROUP BY ns.mat HAVING avg(ns.nota)>=5)
 MINUS
 SELECT s.mat, s.nume, s.prenume FROM studenti s WHERE s.mat in(
 SELECT ns.mat FROM note_studenti ns WHERE ns.nota<5);
--3--
SELECT nume,prenume,ns1.nota from studenti s  inner join note_studenti ns1 on ns1.mat=s.mat WHERE s.mat in (
  SELECT ns.mat from note_studenti ns GROUP BY ns.mat HAVING AVG(ns.nota) > (SELECT AVG(ns2.nota) from note_studenti ns2
  ));
--1.5 p
--varianta corecta:
select nume, prenume
from studenti s inner join note_studenti ns on s.mat=ns.mat
where nota < 5 and s.mat in
  (select mat
  from note_studenti
  group by mat
  having avg(nota)>5);
  
--4--
UPDATE note_studenti ns SET nota=5 where ns.nota<5 and ns.mat=(
  SELECT mat from studenti WHERE nume='nume2');
ROLLBACK;
--3 p

--5--
ALTER TABLE note_studenti ADD ( data_nota DATE DEFAULT SYSDATE );
ALTER TABLE note_studenti DROP COLUMN data_nota;
--3 p

total:10.5 
