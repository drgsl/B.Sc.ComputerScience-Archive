drop table persons;
drop table message;

CREATE TABLE persons
(
    id       NUMBER(38, 0) NOT NULL,
    username VARCHAR2(255),
    CONSTRAINT pk_persons PRIMARY KEY (id)
);

ALTER TABLE persons
    ADD CONSTRAINT uc_persons_username UNIQUE (username);

CREATE TABLE message
(
    id          NUMBER(38, 0) NOT NULL,
    id_sender   NUMBER(38, 0),
    id_receiver NUMBER(38, 0),
    message     VARCHAR2(255),
    CONSTRAINT pk_message PRIMARY KEY (id)
);