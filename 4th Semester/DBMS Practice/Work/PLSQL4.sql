--- PLSQL4 -- Colectii
--CURS--???
--Associativ Arrays---- cheie(index by doar anumit type) - valoare (orice); nu se poate cu CREATE OR REPLACE TYPE -> global
TYPE nume_tip IS TABLE OF tip_element [NOT NULL] INDEX BY [BINARY_INTEGER | PLS_INTEGER | VARCHAR2(dimendiune)];

---Nested tables --- o multime de elemente, dar la parcurgere se considere un index
TYPE nume_tip IS TABLE OF tip_element [NOT NULL]; 

--VARRAYS ---un array cu o limita de elemente de orice tip
TYPE nume_tip IS {VARRAY | VARYING ARRAY} (numar_elemente) OF tip_element [NOT NULL];


---ASSOCIATIV ARRAYS---nu am limita de elemente
DECLARE 
    TYPE MyTab IS TABLE OF NUMBER INDEX BY VARCHAR2(10); --indexul e de tip varchar2 
    varsta MyTab;
BEGIN
   varsta('Gigel') := 3;
   varsta('Ionel') := 4;
   DBMS_OUTPUT.PUT_LINE('Varsta lui Gigel este ' || varsta('Gigel'));
   DBMS_OUTPUT.PUT_LINE('Varsta lui Ionel este ' || varsta('Ionel'));
   
   varsta('Ionel') := 7;
   DBMS_OUTPUT.PUT_LINE('Varsta lui Gigel este ' || varsta('Gigel'));
   DBMS_OUTPUT.PUT_LINE('Varsta lui Ionel este ' || varsta('Ionel'));
END;


DECLARE 
    TYPE MyTab IS TABLE OF studenti%ROWTYPE INDEX BY PLS_INTEGER; --index de tip numar
    linii MyTab;
i PLS_INTEGER:=0;    
BEGIN
--    SELECT * INTO linii(0) FROM studenti WHERE ROWNUM = 1;
--    DBMS_OUTPUT.PUT_LINE(linii(0).prenume);
    
----SAU toata tabela
    for informatii in (select * from studenti) loop
        linii(i):=informatii; 
        i:=i+1;
    end loop;    
--    
    DBMS_OUTPUT.PUT_LINE(linii.count);
    for i in linii.first..linii.last loop
        DBMS_OUTPUT.PUT_LINE(linii(i).id||' '||linii(i).nume||'  '||linii(i).prenume||' '||linii(i).bursa);
    end loop;
END;

--utilizare functii  pentru indexul e de tip varchar2 
  
DECLARE 
    TYPE MyTab IS TABLE OF NUMBER INDEX BY VARCHAR2(10);
    varsta MyTab;
cheie varchar2(10);    
BEGIN
   varsta('Gigel') := 3;
   varsta('Ionel') := 4;
   varsta('Maria') := 6;
   
   DBMS_OUTPUT.PUT_LINE('Numar de elemente in lista: ' || varsta.COUNT);
   
   DBMS_OUTPUT.PUT_LINE('Prima cheie din lista: ' || varsta.FIRST);
   DBMS_OUTPUT.PUT_LINE('Ultima cheie din lista: ' || varsta.LAST);

   DBMS_OUTPUT.PUT_LINE('Inaintea lui Ionel in lista: ' || varsta.PRIOR('Ionel'));
   DBMS_OUTPUT.PUT_LINE('Dupa Ionel in lista: ' || varsta.NEXT('Ionel'));
      
   varsta.DELETE('Maria');   
   DBMS_OUTPUT.PUT_LINE('Dupa Ionel in lista: ' || varsta.NEXT('Ionel'));   
   
--   parcurgere table cu index varchar 
   cheie:=varsta.first;
   while cheie is not null loop
        DBMS_OUTPUT.PUT_LINE('Varsta este '||varsta(cheie));
        cheie:=varsta.next(cheie);
    end loop;
   
END;


----NESTED TABLE-------------- este parse, raman elemente goale
DECLARE
    TYPE prenume IS TABLE OF varchar2(10);
    student prenume;
BEGIN
    student := prenume('Gigel', 'Ionel', 'Maria');  
    student.EXTEND(4,2); -- copii elementul al doilea de 4 ori -> 7 elemente
    student.delete(2); -- sterg elementul al doilea  -> raman 6 elemente (fara primul Ionel)
    DBMS_OUTPUT.PUT_LINE(student.count); -- nr total elemente
    for i in student.first..student.last loop
        if student.exists(i) then -- daca incerc sa afisez ceva ce nu exista se va produce o eroare
           DBMS_OUTPUT.PUT_LINE(i||' - '||student(i));  -- afisam pozitia si valoarea
        end if;
    end loop;
END;

--- cu elemente de tip ROWTYPE (o inregistrare din tabel)
DECLARE 
   TYPE linie_student IS TABLE OF studenti%ROWTYPE;  -- studenti%rowtype daca nu mai folosim cursorul
   lista_studenti linie_student;
BEGIN

   SELECT * BULK COLLECT INTO lista_studenti FROM studenti;  --se pot pune in bulk toate inregistrarile din studenti cu select direct

    for i in lista_studenti.first..lista_studenti.last loop
        if lista_studenti.exists(i) then -- daca incerc sa afisez ceva ce nu exista se va produce o eroare
           DBMS_OUTPUT.PUT_LINE(i||' - '||lista_studenti(i).nume);  -- afisam pozitia si valoarea
        end if;
    end loop;   
    DBMS_OUTPUT.PUT_LINE('Numar studenti: '||lista_studenti.COUNT);
END;

---- sau cu cursor
DECLARE 
   CURSOR curs IS SELECT * FROM studenti;
   TYPE linie_student IS TABLE OF curs%ROWTYPE; 
   lista_studenti linie_student;
BEGIN
   open curs;
        fetch  curs BULK COLLECT INTO lista_studenti;
   close curs;
   
    for i in lista_studenti.first..lista_studenti.last loop
        if lista_studenti.exists(i) then -- daca incerc sa afisez ceva ce nu exista se va produce o eroare
           DBMS_OUTPUT.PUT_LINE(i||' - '||lista_studenti(i).nume);  -- afisam pozitia si valoarea
        end if;
    end loop;   
    DBMS_OUTPUT.PUT_LINE('Numar studenti: '||lista_studenti.COUNT);
END;

---- Parcurgere cu NEXT ----
DECLARE 
   CURSOR curs IS SELECT * FROM studenti;
   TYPE linie_student IS TABLE OF curs%ROWTYPE; 
   lista_studenti linie_student;
   
   i number;
BEGIN
   open curs;
    fetch  curs BULK COLLECT INTO lista_studenti;
   close curs;
   
   i:=lista_studenti.first;
   while i is not null loop
      DBMS_OUTPUT.PUT_LINE(i||' - '||lista_studenti(i).nume);  -- afisam pozitia si valoarea
      i:= lista_studenti.next(i);
    end loop;   
    DBMS_OUTPUT.PUT_LINE('Numar studenti: '||lista_studenti.COUNT);
END;

---VARRAYS ---------
DECLARE
  TYPE varr IS VARRAY(5) OF varchar2(10);
  orase varr;
BEGIN
  orase := varr('Iasi', 'Bacau', 'Suceava', 'Botosani');
  DBMS_OUTPUT.PUT_LINE('Numar orase: '||orase.COUNT);
  orase.TRIM;
  FOR i IN orase.FIRST..orase.LAST LOOP
     DBMS_OUTPUT.PUT_LINE(orase(i));
  END LOOP;
  
  orase.EXTEND(2);
  orase(4):='Sibiu';
  orase(5):='Brasov';
  DBMS_OUTPUT.PUT_LINE('Dupa adaugare:');
  FOR i IN orase.FIRST..orase.LAST LOOP
     DBMS_OUTPUT.PUT_LINE(orase(i));
  END LOOP;  
END;

--------TIPUL RECORD AVETI EXEMPLU IN LABORATOR------------------


--------------EXERCITIU FINAL---------------
----------------------------------------------------------------------------------------
Adaugati o coloana noua la tabelul studenti cu denumirea “lista_medii” de tip 
nested table in care se vor adauga mediile semestriale ale studentilor (
din anul 1 sem 1, an 1 sem 2, an 2 sem 1 etc.). Campul de medii va fi extins 
doar cat este necesar (nu va contine decat locatii pentru mediile existente si 
nu 6 pentru fiecare medie posibil existenta). 
Construiti o functie care pentru un anumit student returneaza cate medii are 
trecute in coloana “lista_medii”.

drop type lista_medii;
/
CREATE OR REPLACE TYPE lista_medii AS TABLE OF number;
/
drop table stud;
/
create table stud as select * from studenti;
/
alter table stud add medii lista_medii nested table medii store as ceva1;
/
--alter table stud drop column medii
--drop type lista_medii;
-- drop table stud;

create or replace function nr_medii(p_id studenti.id%type) return number is
sir lista_medii;
begin
    select medii into sir from stud where id=p_id;
    return sir.count;
end;

set serveroutput on;
declare
cursor stud_info is select * from stud; 
cursor c_medii (v_id studenti.id%type) is 
    select avg(valoare) media
               from note n join cursuri c on n.id_curs=c.id 
               where n.id_student=v_id
               group by n.id_student, c.an, c.semestru;

sir lista_medii:=lista_medii();
begin

for linie in stud_info loop
    DBMS_OUTPUT.PUT('Mediile pentru stud '||linie.id||' sunt: ');
    for v_index in c_medii(linie.id) loop
        sir.extend(1);
        sir(sir.count):= v_index.media;
        DBMS_OUTPUT.PUT('  '||sir(sir.count));
    end loop;
     
    update  stud set medii=sir where id=linie.id ;
    sir.delete;
    DBMS_OUTPUT.PUT_LINE(stud_info%rowcount||'. Studentul '||linie.nume||' '||linie.prenume||' '||linie.id||' are '||nr_medii(linie.id)||' medii');
end loop;
--rollback;
end;


select medii from stud;
insert into stud values(1026, 'AB1', 'A', 'B', 3, 'B1',null, null, null, null, null, null);

alter table stud drop column medii;
/
drop type lista_medii;
/
drop table stud;
/