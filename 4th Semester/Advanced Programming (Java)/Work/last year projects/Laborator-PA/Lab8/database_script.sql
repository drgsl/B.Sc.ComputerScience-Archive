-- id, title, release_date, duration, score
create table movies (
    id int not null primary key,
    title varchar2(255) not null,
    release_date date,
    duration int,
    score int
);

-- id, name (for example: Action, Drama)
create table genres (
    id int not null primary key,
    name varchar2(255) not null
);

create table movies_genres (
    movie_id int not null,
    genre_id int not null,
    constraint fk_movies foreign key(movie_id) references movies(id),
    constraint fk_genres foreign key(genre_id) references genre(id)
);

create table actors (
    id int not null primary key,
    name varchar2(255) not null,
    salary int not null,
    movie_id int not null,

    constraint fk_movie foreign key(movie_id) references movies(id)
);

create table directors (
    id int not null primary key,
    name varchar2(255) not null,
    salary int not null,
    movie_id int not null,

    constraint fk_movie foreign key(movie_id) references movies(id)
);

