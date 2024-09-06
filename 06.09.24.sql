-- DDL - Data Definition Language
-- CREATE, DROP, ALTER, TRUNCATE

-- DML
-- DCL
-- TCL

CREATE DATABASE HelloWorld

CREATE TABLE "public"."hello_world"
(
    "surname" VARCHAR NOT NULL,
    "name" VARCHAR NOT NULL,
    "patronymic" VARCHAR NOT NULL,
    "birth_date" DATE NOT NULL,
    "sex" BOOLEAN NOT NULL,
    "course" INT NOT NULL,
    "group" VARCHAR NOT NULL,
    "diploma_theme" VARCHAR NULL
)

ALTER TABLE "public"."hello_world"
    ADD CONSTRAINT "CHK_smth" CHECK ("course" BETWEEN 1 AND 5);