--- ex1

select nume,prenume
from studenti
where mat=
(
select mat from
(
select mat,avg(nota)
from note_studenti
group by mat 
having avg(nota) >= all
(
select avg(nota) 
from note_studenti
group by mat
)))
;


			


--- ex2
select nume,prenume
			from studenti
			where mat in 
			(
			  select mat 
			  from note_studenti
			  where nota <5
			)
and mat in 
(
select mat
from (
select mat,avg(nota)
from note_studenti
group by mat 
having avg(nota)>5 
)
)
;


			select nume,prenume
			from studenti
			where mat in 
			(
			  select mat 
			  from note_studenti
			  where nota <5
			)
			and mat in
			(
			select mat
			from
			(
			select avg(nota) as medie,mat
			from note_studenti
			group by mat
			) where medie >=5);


--- ex3
			select denumire_obiect,studenti.nume as nume_strundet,medie_obiect,note_studenti.nota
			from
			(
			select round(avg(nota),2) as medie_obiect,den as denumire_obiect,ob.cod as CODobiect
			from note_studenti ns,obiecte ob
			where ns.cod=ob.cod
			group by den,ob.cod
			),note_studenti,studenti
			where note_studenti.cod=CODobiect and medie_obiect<note_studenti.nota and note_studenti.mat=studenti.mat
			;


--- ex4
--- datele lui nume2 la inceput
			select *
			from note_studenti
			where mat=
			(
			select mat
			from studenti
			where nume = 'nume2');

			--- modificarea datelor lui nume2
			update note_studenti
			set nota =5
			where (mat,nota) in
			(
			select mat,nota
			from note_studenti
			where mat=
			(
			select mat
			from studenti
			where nume = 'nume2')
			and nota<5);

			--- datele lui nume2 dupa modificari
			select *
			from note_studenti
			where mat=
			(
			select mat
			from studenti
			where nume = 'nume2');
			
ROLLBACK;
			
      
     
--- ex5
			alter table note_studenti add (Ddata date default sysdate);
			select * 
			from note_studenti;
			alter table note_studenti drop column Ddata;
            select * 
			from note_studenti;