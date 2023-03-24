/*Subiectul 1
========================
Afisati angajatii veniti in firma in luna iunie.*/
select ename,hiredate,to_char(hiredate,'Month')Luna_Angajare
from emp
where trim(to_char(hiredate,'Month'))='June'

/*Subiectul 2 
========================
Afisati toti subalternii lui Ford si data de angajare pentru cei care au gradele de 
salarizare 1,2 si 3.*/
select e.ename,e.hiredate,lpad(e.sal,7)sal
from emp e inner join emp m on e.mgr=m.empno inner join salgrade s on e.sal between losal and hisal
where m.ename='Ford' and grade in(1,2,3) 

/*Subiectul 3
========================
Sa se afiseze angajatii si departamentul in care-si desfasoara activitatea, 
pentru cei care lucreaza in departamentul cu cel mai slab platit angajat din firma.*/



/*Subiectul 4
========================
Adaugati o coloana INFO(VARCHAR2(60)) in tabela emp astfel incit informatia 
de aici sa fie completata astfel:
<ename>lucreaza in <loc>si are comision<comm>
iar daca nu are comision se va afisa:
<ename>lucreaza in <loc>si nu are comision

doar pentru angajatii care au salariul mai mare de 1500.

Coloana loc se va lua din tabela dept !!
Afisati INREGISTRARILE MODIFICATE (doar acestea !!) folosind coloane SEMNIFICATIVE.
In final, reveniti la situatia initiala (si ca date si ca structura a tabelei emp). 

De ex. ptr. ZLOTKEY coloana INFO va fi de forma:  
		ZLOTKEY lucreaza in Oxford si are comision .2*/
    


/*Subiectul 5 
========================
Afisati toti subalternii lui King si data de angajare pentru cei care au gradul de 
salarizare 4.*/
select e.ename,e.hiredate,e.sal
from emp e inner join emp m on e.mgr=m.empno inner join salgrade on e.sal between losal and hisal 
where m.ename='King' and grade=4

/*Subiectul 6
========================
Sa se afiseze managerul cu cea mai MICA suma salariala a subordonatilor lui
pentru acei manageri care lucreaza in New York (campul loc din tabela dept)*/ 



