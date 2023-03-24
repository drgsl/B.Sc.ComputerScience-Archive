create table countries(
    id serial primary key,
    name varchar(50) not null,
    continent_id int not null,
    FOREIGN KEY (continent_id) REFERENCES continents(id)
);

create table continents(
    id serial primary key,
    name varchar(20) not null
);

CREATE SEQUENCE dept_seq START WITH 1;
CREATE SEQUENCE country_seq START WITH 1;

CREATE OR REPLACE TRIGGER dept_bir
    BEFORE INSERT ON CONTINENTS
    FOR EACH ROW

BEGIN
    SELECT dept_seq.NEXTVAL
    INTO   :new.id
    FROM   dual;
END;

CREATE OR REPLACE TRIGGER country
    BEFORE INSERT ON COUNTRIES
    FOR EACH ROW

BEGIN
    SELECT country_seq.NEXTVAL
    INTO   :new.id
    FROM   dual;
END;

drop trigger country;
drop table countries;
delete from continents where id=2;

create table cities(
    id serial primary key,
    country_id int not null,
    name varchar(50) not null,
    capital int check(capital=0 or capital=1) not null,
    latitude float not null,
    longitude float not null,
    FOREIGN KEY (country_id) REFERENCES countries(id)
);

CREATE SEQUENCE city_seq START WITH 1;

CREATE OR REPLACE TRIGGER city
    BEFORE INSERT ON CITIES
    FOR EACH ROW
BEGIN
    SELECT city_seq.NEXTVAL
    INTO   :new.id
    FROM   dual;
END;

    drop table cities;