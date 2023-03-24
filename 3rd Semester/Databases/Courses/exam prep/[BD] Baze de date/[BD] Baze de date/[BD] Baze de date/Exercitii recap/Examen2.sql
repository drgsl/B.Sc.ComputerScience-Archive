/*Subiectul 2
========================
Sa se afiseze agentul (sau agentii) care vind(e) cele mai multe produse pe o factura (numarul de produse
de pe aceeasi factura care apar la acelasi client)*/


/*Subiectul 3
========================
Sa se afiseze numele departamentelor (dname din dept) in care lucreaza angajatii si maximul salarial 
pe fiecare din aceste departamente. Veti numi coloanele Departament, respectiv Max_Sal, exact cu aceste tip de 
caractere.*/
select dname Departament,lpad(max(sal),7)Max_Sal
from emp e inner join dept d on e.deptno=d.deptno
group by dname
order by Max_Sal desc

/*Subiectul 4
========================
Folosind clauza With afisati diferenta intre suma salariilor celor care lucreaza in  
New York si cei care lucreaza in Dallas (veti folosi campul loc din tabela dept !!).*/

with
sal_new_york as
(select sum(sal) as sum_new_york
from emp e inner join dept d on e.deptno=d.deptno
where loc='New York'),
sal_dallas as
(select sum(sal) as sum_dallas
from emp e inner join dept d on e.deptno=d.deptno
where loc='Dallas')
select sum_new_york,sum_dallas,sum_new_york-sum_dallas 
from sal_new_york,sal_dallas

/*Subiectul 5
========================
Sa se modifice salariile angajatilor care lucreaza intr-un departament (dname din dept) 
dat ca parametru cu in sensul adaugarii la valoarea curenta, a o zecea parte din codul departamentului aferent. 
Afisati angajatii, noile salarii si codul departamentului aferent. Reveniti la datele initiale.*/ 


