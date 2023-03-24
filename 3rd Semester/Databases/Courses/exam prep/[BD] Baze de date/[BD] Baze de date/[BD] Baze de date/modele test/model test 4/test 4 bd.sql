--- ex1
select nume
from profesori
where cod in
(
select cod
from note_elevi
where nota in
(
  select min(nota)
  from note_elevi
)
);

--- ex2
select nume,avg(nota)
from elevi,note_elevi
where elevi.matricola=note_elevi.mat
and nota >=5
group by nume;


--- ex3
select profesor,elevi.nume as nume_elev ,medie_profesori,note_elevi.nota
from
(select nume as profesor,medie_profesori , profesori.cod as profesoriCODfacut
from(
select round(avg(nota),2) as medie_profesori,cod as cod_profesor
from note_elevi
group by cod) NOTE_ELEVI,profesori 
where profesori.cod = cod_profesor),elevi,note_elevi
where elevi.matricola=note_elevi.mat and medie_profesori>note_elevi.nota and profesoriCODfacut = note_elevi.cod;



--- ex4
select * from note_elevi;
alter table note_elevi add (Ddata date default sysdate);
select * from note_elevi;
alter table note_elevi drop column Ddata;
select * from note_elevi;


--- ex5
update note_elevi
set nota = nota+1
where (nota,cod) in
(
select nota,note_elevi.cod
from note_elevi,profesori
where profesori.nume='nume1' and nota<10 and profesori.cod = note_elevi.cod
);