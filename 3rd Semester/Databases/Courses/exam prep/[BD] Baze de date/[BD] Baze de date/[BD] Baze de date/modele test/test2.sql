
-- problema 1.
SELECT rezultat.nume, rezultat.suma 
FROM ( 
        SELECT con.nume, SUM(inc.suma) suma
        FROM contribuabili con JOIN incasari inc ON con.cod = inc.codc
        GROUP BY con.nume
        HAVING SUM(inc.suma) = (
            SELECT * FROM (
                 SELECT SUM(inc.suma)
                 FROM contribuabili con JOIN incasari inc ON con.cod = inc.codc
                 GROUP BY con.nume
                 ORDER BY SUM(inc.suma) DESC
                 )
            WHERE ROWNUM < 2
        )
        ORDER BY SUM(inc.suma) DESC
     ) rezultat
;

-- problema 3.
SELECT *
FROM (
        SELECT tax.den, SUM(inc.suma)
        FROM taxe tax JOIN incasari inc ON tax.cod = inc.codt
        GROUP by tax.den
        ORDER BY SUM(inc.suma) DESC
      )
WHERE ROWNUM < 4;

-- problema 4.
UPDATE incasari inc
SET inc.suma = (inc.suma + inc.suma * 0.1)
WHERE 
  inc.codt IN (
               SELECT tax.cod
               FROM taxe tax
               WHERE tax.tip = 2 
             )
;
-- rollback;
 
4.
select codc,suma
			from incasari
			where codt in
			(
			select cod
			from taxe
			where tip=2);
      
update incasari
set suma=suma+suma*0.01
where (codt,suma) in
( select codt, suma
from incasari
			where codt in
			(
			select cod
			from taxe
			where tip=2)
      );

rollback;

 
 
 -- problema 5.
 ALTER TABLE contribuabili
 ADD 
   (
    adresa VARCHAR(15) DEFAULT 'Iasi' NOT NULL
   );

-- verificare inserare 
SELECT * FROM contribuabili;

ALTER TABLE contribuabili
 DROP COLUMN
        adresa;

-- rollback;























