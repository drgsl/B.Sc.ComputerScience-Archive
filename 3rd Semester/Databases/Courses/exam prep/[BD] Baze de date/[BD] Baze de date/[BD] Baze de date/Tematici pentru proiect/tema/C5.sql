--view
drop view Trat;
create view Trat as
select IDTratament, Tratament
from Boli
where IDFisa = '3';

select * from Trat;
select * from Boli;

delete from Trat where Tratament = 'operatie';

select * from Trat;
select * from Boli;

--VIEW + TRIGGER
drop view Trat;
create view Trat as
select IDTratament, Tratament
from Boli
where IDFisa = '3';

select * from Trat;
select * from Boli;

drop trigger TratDelete;
create trigger TratDelete
instead of delete on Trat
for each row
begin
  delete from Boli
  where IDTratament = :Old.IDTratament
  and Tratament = :Old.Tratament
  and IDFisa = '3';
end;
/
delete from Trat where Tratament = 'operatie';

select * from Trat;
select * from Boli;	

/
