--Nistor G. Daniel, A7

--1.
--SELECT nume, prenume
--FROM (SELECT 
--SELECT max(nota) FROM note_studenti GROUP BY mat;



--4.
SELECT studenti.mat, nota, nume
FROM note_studenti INNER JOIN studenti ON studenti.mat = note_studenti.mat
WHERE nume = 'nume2' AND nota < 5;

UPDATE note_studenti
SET note_studenti.nota = 5
WHERE note_studenti.mat IN (SELECT studenti.mat
      FROM note_studenti INNER JOIN studenti ON studenti.mat = note_studenti.mat
      WHERE nume = 'nume2') AND note_studenti.nota IN (SELECT nota
            FROM note_studenti WHERE nota < 5);

SELECT * from note_studenti;

ROLLBACK;
--3p, dar te-ai complicat foarte mult !
--o varianta mai usoara:
update note_studenti 
set nota = 5
where nota < 5 and mat in 
  (select mat 
  from studenti 
  where lower(nume) = 'nume2'); 


--5.
ALTER TABLE note_studenti
ADD data_nota date DEFAULT sysdate;

SELECT * FROM note_studenti;

ALTER TABLE note_studenti
DROP COLUMN data_nota;

SELECT * FROM note_studenti;
--3 p

total: 6 p