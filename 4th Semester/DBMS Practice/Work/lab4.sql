DROP TYPE student_info_list;
DROP TYPE student_info;

CREATE OR REPLACE TYPE student_info AS OBJECT (
    id_student NUMBER,
    media FLOAT,
    nr_restante NUMBER,
    nr_prieteni NUMBER
);

CREATE OR REPLACE TYPE student_info_list IS TABLE OF student_info;


DECLARE
    studenti_info student_info_list := student_info_list();
BEGIN
    FOR s IN (SELECT id, nume, prenume FROM studenti)
    LOOP
        -- calculam media si numarul de restante
        SELECT AVG(valoare), COUNT(*) INTO s.media, s.nr_restante
        FROM note   
        WHERE id_student = s.id
        AND valoare < 5;

        -- calculam numarul de prieteni
        SELECT COUNT(*) INTO s.nr_prieteni
        FROM prieteni
        WHERE id_student1 = s.id
        OR id_student2 = s.id;

        -- adaugam informatiile in colectie
        studenti_info.extend;
        studenti_info(studenti_info.count) := student_info(s.id, s.media, s.nr_restante, s.nr_prieteni);
    END LOOP;

    -- afisam informatiile
    FOR i IN 1..studenti_info.count LOOP
        DECLARE
            nume_student VARCHAR2(100);
            prenume_student VARCHAR2(100);
        BEGIN
            -- extragem numele si prenumele studentului pe baza id-ului
            SELECT nume, prenume INTO nume_student, prenume_student
            FROM studenti
            WHERE id = studenti_info(i).id_student;
             -- afisam informatiile despre student
        DBMS_OUTPUT.PUT_LINE('Studentul ' || nume_student || ' ' || prenume_student || ' cu id-ul ' || studenti_info(i).id_student || ' are:');
        DBMS_OUTPUT.PUT_LINE('Media ' || studenti_info(i).media);
        DBMS_OUTPUT.PUT_LINE('Restante ' || studenti_info(i).nr_restante);
        DBMS_OUTPUT.PUT_LINE('Nr amici ' || studenti_info(i).nr_prieteni);
    END;
END LOOP;
END;

