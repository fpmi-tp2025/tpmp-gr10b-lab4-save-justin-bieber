-- Created by Vertabelo (http://vertabelo.com)
-- Last modification date: 2025-04-10 09:13:38.21

-- tables
-- Table: CD
CREATE TABLE CD (
    cd_id integer NOT NULL CONSTRAINT CD_pk PRIMARY KEY,
    release_date date,
    manufacturer text,
    price decimal(10,2)
);

-- Table: Songs
CREATE TABLE Songs (
    id integer NOT NULL CONSTRAINT Songs_pk PRIMARY KEY AUTOINCREMENT,
    song_name text,
    author text,
    performer text,
    cd_id integer NOT NULL,
    CONSTRAINT Songs_CD FOREIGN KEY (cd_id)
    REFERENCES CD (cd_id)
);

-- Table: Transactions
CREATE TABLE Transactions (
    id integer NOT NULL CONSTRAINT Transactions_pk PRIMARY KEY AUTOINCREMENT,
    date date,
    amount integer,
    type text,
    cd_id integer NOT NULL,
    CONSTRAINT Transactions_CD FOREIGN KEY (cd_id)
    REFERENCES CD (cd_id),
    CONSTRAINT type_check CHECK (type IN ('поступление', 'продажа'))
);

-- End of file.

