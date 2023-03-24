DECLARE
CURSOR dept_cursor IS
	SELECT deptno
		FROM dept;
CURSOR emp_cursor IS
	SELECT *
		FROM emp
		ORDER BY empno DESC;
nr NUMBER;
BEGIN
FOR idept IN dept_cursor
LOOP
    nr:=2;
    FOR iemp IN emp_cursor
    LOOP
	EXIT WHEN nr=0;	
	IF iemp.deptno = idept.deptno THEN
		DELETE FROM emp e
			WHERE e.empno = iemp.empno;
		nr:=nr-1;
	END IF;
    END LOOP;
END LOOP;
END;
   /
