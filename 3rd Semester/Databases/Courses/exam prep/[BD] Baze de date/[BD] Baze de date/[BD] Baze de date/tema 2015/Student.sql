
CREATE OR REPLACE PROCEDURE pow (p_baza IN Integer := 3, p_exponent IN INTEGER DEFAULT 5, p_out OUT Integer) AS   
BEGIN
    p_out := p_baza ** p_exponent;    
END;















drop index x;
create index x on studenti(an asc, nume desc);





select * from studenti order by nume desc, an asc;



create index numa on studenti(nume);
drop index numa;
select nume from studenti where nume='Popescu';

create index p on studenti(nume, prenume,nr_matricol,an);
drop index p;

create index c on studenti(nr_matricol, upper(nume));
drop index c;

create index d on studenti(upper(nume), nr_matricol);
drop index d;


create index e on studenti(reverse(upper(nume)));
drop index e;

select nr_matricol, nume, prenume from studenti where reverse(upper(nume)) like reverse('%I%ESC%');
select nr_matricol, nume, prenume from studenti where upper(nume) like '%ESC%' and nr_matricol='111';
select nr_matricol, nume, prenume from studenti where nume='P';
update studenti set prenume='Bog' where nume='Popescu';
insert into studenti values('300','P','o',3,'A5',4,null);


select nr_matricol, nume, prenume from studenti where prenume='Bogdan' and nr_matricol='111';
select nr_matricol, nume, prenume from studenti where nume= 'Popescu' and  nr_matricol='111';
select nr_matricol, nume, prenume from studenti where nr_matricol='111' and nume='Popescu' and prenume='Bogdan' and an=3;
select nr_matricol, nume, prenume from studenti where nr_matricol='111' and prenume='Bogdan';
select nr_matricol, nume, prenume from studenti where nume='Popescu' and an=3;

select * from (select * from studenti order by nume asc) where rownum<6;
