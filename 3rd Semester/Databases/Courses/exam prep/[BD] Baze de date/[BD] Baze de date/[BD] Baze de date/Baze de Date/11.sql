DECLARE
CURSOR dept_cursor IS
  SELECT *
    FROM dept;
CURSOR emp_cursor IS
  SELECT *
    FROM emp;
i NUMBER;
BEGIN
FOR idept IN dept_cursor
LOOP
    i:=1;
    FOR iemp IN emp_cursor
    LOOP
	IF iemp.deptno = idept.deptno THEN
		IF mod(i,2) = 0 THEN
			dbms_output.put_line(iemp.ename || iemp.deptno || '     ' || iemp.empno);
			DELETE FROM emp e
				WHERE e.empno = iemp.empno;
		END IF;
		i:=i+1;
	END IF;
    END LOOP;
END LOOP;
END;
   /