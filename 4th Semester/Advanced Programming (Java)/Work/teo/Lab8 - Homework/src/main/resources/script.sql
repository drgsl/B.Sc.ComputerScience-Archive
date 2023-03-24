create table continents(
                           id int not null primary key,
                           name varchar2(50)
);


create table countries(
                          id int not null primary key,
                          name varchar2(50),
                          code number,
                          continent_id int,
                          FOREIGN KEY (continent_id) REFERENCES continents(id)
);

create table cities(
                       id int not null primary key,
                       country_id int not null,
                       name varchar2(50),
                       capital int constraint ch_capital check (capital in (0,1)),
                       latitude binary_double not null,
                       longitude binary_double not null,
                       FOREIGN KEY (country_id) REFERENCES countries(id)
);

drop table cities;
drop table countries;
drop table continents;

select * from continents;

delete from countries;
delete from continents;

CREATE SEQUENCE continents_seq START WITH 1;
CREATE SEQUENCE countries_seq START WITH 1;
CREATE SEQUENCE cities_seq START WITH 1;

drop sequence cities_seq;
drop sequence countries_seq;
drop sequence continents_seq;

commit;

CREATE OR REPLACE TRIGGER continents_trigger
BEFORE INSERT ON continents
FOR EACH ROW
BEGIN
SELECT continents_seq.NEXTVAL
INTO   :new.id
FROM   dual;
END;

CREATE OR REPLACE TRIGGER countries_trigger
BEFORE INSERT ON countries
FOR EACH ROW
BEGIN
SELECT countries_seq.NEXTVAL
INTO   :new.id
FROM   dual;
END;

CREATE OR REPLACE TRIGGER cities_trigger
BEFORE INSERT ON cities
FOR EACH ROW
BEGIN
SELECT cities_seq.NEXTVAL
INTO   :new.id
FROM   dual;
END;

drop trigger cities_trigger;


insert into continents(name) values('Europa');
insert into continents(name) values('Asia');

insert into countries(name, code, continent_id) values('Romania', 594, 1);
insert into countries(name, code, continent_id) values('Polonia', 590, 1);

delete from cities where id > 0;
delete from countries where id > 0;
delete from continents where id > 0;
delete  from fake_cities where id>0;
delete from sisters where sister1>0;

commit;
