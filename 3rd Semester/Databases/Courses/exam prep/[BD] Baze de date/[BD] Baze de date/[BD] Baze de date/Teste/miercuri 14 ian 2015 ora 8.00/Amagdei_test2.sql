desc studenti;


--1 
select s.nume Nume, s.prenume Prenume
from studenti s inner join note_studenti n on  n.mat = s.mat
where avg((nvl(n.nota,0)) = (select max(avg(nvl(ns.nota,0))
                        from studenti ns inner join note_studenti ns on ns.mat = st.mat);
--unde e havingul din selectul principal?
--unde e group by din subinterogare? ai dubla agregare, max(avg) - se cere automat group by !
--nu am ce sa iti dau la punctul asta, toata "smecheria" era legata de having / group by !
--0 p
  
  --2 
select nume, prenume 
from studenti s inner join note_studenti n on s.mat = n.mat
where n.nota < 5 and 5>= (select avg(nvl(nt.nota,0)
                      from studenti st inner join note_studenti nt on  nt.mat = st.mat);
--aveai nevoie de having in subinterogare
--1.5 p
--varianta corecta:
select nume, prenume
from studenti s inner join note_studenti ns on s.mat=ns.mat
where nota < 5 and s.mat in
  (select mat
  from note_studenti
  group by mat
  having avg(nota)>5);
                      
--4
update note_studenti
set nota = 5
where nota < 5 and mat = (select distinct m.mat
                          from note_studenti m inner join studenti s on s.mat = m.mat
                          where s.nume = 'nume2');
select * 
from note_studenti m inner join studenti s on s.mat = m.mat where s.nume = 'nume2';

rollback;
--3 p
--5 

alter table note_studenti add(data_nota date);
update note_studenti set data_nota = sysdate 
where data_nota is null;
rollback;
--3 p

total:7.5 p


