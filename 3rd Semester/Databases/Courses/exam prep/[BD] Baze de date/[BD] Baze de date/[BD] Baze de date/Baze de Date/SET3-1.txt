
SELECT TO_CHAR( SYSDATE ,'DD-Mon-YYYY HH:MI:SS') AS "Date" FROM DUAL;
/

SELECT ename, hiredate, TO_CHAR(NEXT_DAY(ADD_MONTHS(hiredate, 6),'MONDAY'), 'fmDay, "the" Ddspth "of" Month, YYYY')  Review FROM emp;  
/

SELECT ename, ROUND(MONTHS_BETWEEN( SYSDATE, hiredate)) MONTHS_WORKED 
				FROM   emp  
					ORDER BY months_worked;
/

SELECT  ename || ' earns '    || TO_CHAR(sal, 'fm$99,999.00')  || ' monthly but he wants ' || TO_CHAR(sal * 3, 'fm$99,999.00') || '.' "Dream Salaries" 
/
							FROM    emp;

SELECT ename, 
       LPAD(sal, 15, '$') SALARY 
      FROM emp;
/

 SELECT	INITCAP(ename) "Name",
       LENGTH(ename) "Length"
       FROM     emp
       WHERE    ename LIKE 'J%'
       OR       ename LIKE 'M%'
       OR       ename LIKE 'A%'
       ORDER BY ename;
/

SELECT ename, hiredate, 
       TO_CHAR(hiredate, 'DAY') DAY 
	FROM   emp 
	ORDER BY TO_CHAR(hiredate - 1, 'd');
/

SELECT ename, 
       NVL(TO_CHAR(comm), 'No Commission') COMM 
       FROM   emp;     
/


