/*
 * 2.
 */

INSERT INTO CONTRACTE VALUES(77,TO_DATE('5-10-2010','dd-mm-yyyy'),77,77,TO_DATE('5-10-2012','dd-mm-yyyy'));
INSERT INTO ARTICOLE VALUES(77,77,100,543);
INSERT INTO LIVRARI VALUES(77,77,100,TO_DATE('20-5-2011','dd-mm-yyyy'));

/*
 * 3. Pentru fiecare inregistrare  din CONTRACTE  sa se afiseze denumirea
 * societatii beneficiare cu capitalul social respectiv, precum si denumirea
 * societatii furnizoare cu capitalul social respectiv.
 */

select s.dens "Societate",s.capital "Capital",s.tipsoc "tipul societatii"
from contracte c,societati s
where s.cods in(c.codb,c.codf);

/*
 * 4. Pentru fiecare contract sa se calculeze valoarea totala a sa.
 */
SELECT c.codc,SUM(a.pret*a.cant) "Valoarea totala"
FROM contracte c,articole a
WHERE c.codc=a.codca
GROUP BY c.codc;

/*
 * 5. Pentru fiecare contract CODC si produs CODP sa se calculeze
 * cantitatea totala livrata din CODP la contractul CODC
 */

SELECT codc "COD CONTRACT", codp"COD PRODUS", SUM(cantl) "CANTITATE"
FROM CONTRACTE, PRODUSE, LIVRARI
WHERE codc=codcl 
AND codp=codpl
GROUP BY codc, codp
ORDER BY codc;

/*
 * 6. Pentru fiecare inregistrare din CONTRACTE  sa se afiseze inregistrarea
 * din CONTRACTE apoi toate articolele din contractul respectiv, afisand pentru
 * un produs si denumirea sa si TIPP.
 */
SELECT c.codc "Cod contract",p.denp "Den produs" ,p.tipp "Tipul produsului"
FROM contracte c,articole a,produse p
WHERE c.codc=a.codca 
AND a.codpa=p.codp
ORDER BY c.codc;

/*
 * 7. Sa se afiseze contractele care au fost realizate integral.
 */
SELECT l.codcl "cod contract" FROM livrari l,articole a
WHERE l.codpl=a.codpa
GROUP BY l.codcl
HAVING SUM(a.cant)=SUM(l.cantl)

/*
 * 8. Pentru fiecare contract nerealizat integral sa se calculeze 
 * datorate de CODB lui CODF,stiind ca penalitatea pentru o zi intirziere si
 * o unitate de produs este de 0,001 RON.
 */
SELECT l.codcl "Cod contract", c.codb "Cod beneficiar", c.codf "Cod Furnizor", (SYSDATE-c.dataf)*0.001+a.cant*0.001 "Penalitati"
FROM livrari l,articole a, contracte c
WHERE l.codpl=a.codpa
AND l.cantl < a.cant
AND SYSDATE > c.dataf

/*
 * 9. Pentru fiecare produs CODP sa se calculeze cantitatea totala din CODP
 * prevazuta in toate contractele(se va afisa aici si denumirea produsului).
 */
SELECT p.DENP, SUM(a.cant)
FROM produse p, articole a, contracte c
WHERE p.codp=a.codca
AND a.codca=c.codc
GROUP BY p.denp;

/*
 *
 */
SELECT s.dens, NVL(SUM(a.pret*a.cant),0)
FROM societate s, contracte c, articole a
WHERE c.codb=s.cods
AND a.codca=c.codc
group by s.dens