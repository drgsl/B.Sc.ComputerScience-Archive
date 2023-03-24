

create table continents(
                          id serial primary key,
                          name varchar(50) unique not null
);

create table countries(
                          id serial primary key,
                          name varchar(50) unique not null,
                          continent_id int,
                          foreign key (continent_id) references continents(id)
);

create table cities(
                       id serial primary key,
                       name varchar(50) not null,
                       country_id int,
                       population int,
                       foreign key (country_id) references countries(id)
);

create table sisters(
    id serial primary key,
    id_city1 int,
    id_city2 int,
    FOREIGN KEY (id_city1) references cities(id),
    FOREIGN KEY (id_city2) references cities(id)
);

drop table continents;
drop table cities;
drop table countries;
drop table sisters;

ALTER TABLE sisters ADD CONSTRAINT UQ_EmpID_DeptID UNIQUE (id_city1, id_city2);



