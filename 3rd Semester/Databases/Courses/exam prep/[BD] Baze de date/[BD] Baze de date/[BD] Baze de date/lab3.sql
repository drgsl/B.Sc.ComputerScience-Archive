select sysdate as "Astazi" from dual
/
select nume, data_nastere, months_between(sysdate, data_nastere) as "numar luni" from studenti
/
select nume, prenume,data_nastere, to_char(data_nastere,'day') as "zi nastere" from studenti
/
select concat('Elevul ',concat(prenume, concat(' este in grupa ',grupa))) from studenti
/
select nume, prenume, rpad(bursa,10, '$') from studenti
/
select concat(lower(substr(nume,1,1)),upper(substr(nume,2))), length(trim(nume)) from profesori where nume like 'B%'
/
select nume, data_nastere, next_day(to_date(to_char(data_nastere,'dd')||'-'||to_char(data_nastere,'mon')||'-'||to_char(sysdate,'yyyy'),'dd-mon-yyyy'),'saturday') from studenti
/
select nume, prenume, bursa, decode(nvl(bursa,'0'), 450,'Premiul I', 350,'Premiul II',250,'Premiul III',0,'mentiune') as "Premiu" from studenti
/
select nume, initcap(translate(lower(nume), 'ai','ia')) from studenti
/
 select nume,data_nastere,cast( floor(months_between(sysdate, data_nastere)/12)||' ani '||mod(floor(months_between(sysdate,data_nastere)),12)||' luni '||floor(sysdate-add_months(data_nastere,floor(months_between(sysdate,data_nastere))))||' zile ' as varchar(25)) as "Ani" from studenti
/
select data_nastere,cast(floor(add_months(data_nastere, ceil((sysdate-data_nastere)/365)*12)-sysdate) as varchar(23)) as "zile pana la aniversare" from studenti
/
select nume, decode(nvl(bursa,'0'),450,450*1.1,350,350*1.15,250,250*1.2,0,0) from studenti
/
select nume,cast(concat(lpad(' ',10-bursa/50,' '),lpad('*',bursa/50,'*'))as varchar(10)) from studenti where bursa is not null
/
