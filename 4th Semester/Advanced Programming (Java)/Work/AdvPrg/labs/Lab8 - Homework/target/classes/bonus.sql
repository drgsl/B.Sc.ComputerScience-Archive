create table fake_cities(
                            id int not null primary key,
                            name varchar2(50)
);

CREATE SEQUENCE fake_seq START WITH 1;
drop sequence fake_seq;

CREATE OR REPLACE TRIGGER fake_trigger
    BEFORE INSERT ON FAKE_CITIES
    FOR EACH ROW
BEGIN
SELECT fake_seq.NEXTVAL
INTO   :new.id
FROM   dual;
END;

delete from fake_cities where id>0;
delete from sisters where sister1>0;

create table sisters(
                        sister1 int not null,
                        sister2 int not null
);
