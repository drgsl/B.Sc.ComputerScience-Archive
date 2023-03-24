1'. SELECT ename FROM emp WHERE TO_CHAR (hiredate, 'YYYY') > 1981
/
2'. SELECT ename, ROUND ( CURRENT_DATE - hiredate, 0 ) "NumberDays", job FROM emp WHERE comm IS NULL ORDER BY "NumberDays" ASC
/
3'. SELECT Replace(ename,'I','Y') "ENAME" FROM emp
/
SELECT ENAME "nume", HIREDATE ,TO_CHAR(ADD_MONTHS(HIREDATE,32*12)) "data",
MONTHS_BETWEEN(SYSDATE,HIREDATE) "nr de luni",SAL+SAL*0.1 "sal marit"
FROM EMP
/
4'. SELECT ename "nume",
Add_Months( hiredate, 32*12 ) "data",
Months_Between( Add_Months( hiredate, 32*12 ), Sysdate ) "nr de luni",
sal + sal * 0.1 "sal marit"
FROM EMP
/
5'. SELECT ename,sal+0.01*Months_Between(hiredate,date'2000-01-01') AS "SAL"
FROM emp
/
6'.  SELECT INITCAP ( ename ) "Name",
DECODE (NVL(comm,-1), -1, ROUND ((sal * TRUNC ( Months_Between( Current_date,hiredate), 12 ) * 0.01), 2),ROUND ((sal * TRUNC ( MONTHS_BETWEEN ( CURRENT_DATE, hiredate), 12 ) * 0.005), 2)) "Salary" FROM emp
/