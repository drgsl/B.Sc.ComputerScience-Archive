DROP TABLE games;
DROP TABLE users;
DROP TABLE library;
DROP TABLE developers;
DROP TABLE categories;
DROP TABLE comments;

CREATE TABLE games (
    id NUMBER(1) PRIMARY KEY,
    name VARCHAR2(50) UNIQUE NOT NULL,
    price NUMBER(3) NOT NULL,
    id_developer NUMBER(1),
    release_date DATE,
    rating NUMBER(3)
);

CREATE TABLE users (
    id NUMBER(1) PRIMARY KEY,
    username VARCHAR2(50) UNIQUE NOT NULL,
    password VARCHAR2(50) NOT NULL,
    data_created DATE
);

CREATE TABLE library (
    id_user NUMBER(1),
    id_game NUMBER(1)
);

CREATE TABLE developers (
    id NUMBER(1) PRIMARY KEY,
    name VARCHAR2(50) UNIQUE NOT NULL
);

CREATE TABLE categories (
    id_game NUMBER(1),
    name VARCHAR2(50) UNIQUE NOT NULL
);

CREATE TABLE comments (
    id NUMBER(1) PRIMARY KEY,
    id_user NUMBER(1),
    id_game NUMBER(1)
);



ALTER TABLE games ADD CONSTRAINT gamesREFdev
    FOREIGN KEY (id_developer) REFERENCES developers (id);

ALTER TABLE library ADD CONSTRAINT libraryREFuser
    FOREIGN KEY (id_user) REFERENCES users (id);
    
ALTER TABLE library ADD CONSTRAINT libraryREFgame
    FOREIGN KEY (id_game) REFERENCES games (id);

ALTER TABLE categories ADD CONSTRAINT categoriesREFgame
    FOREIGN KEY (id_game) REFERENCES games (id);

ALTER TABLE comments ADD CONSTRAINT commentsREFuser
    FOREIGN KEY (id_user) REFERENCES users (id);

ALTER TABLE comments ADD CONSTRAINT commentsREFgame
    FOREIGN KEY (id_game) REFERENCES games (id);

COMMIT;
