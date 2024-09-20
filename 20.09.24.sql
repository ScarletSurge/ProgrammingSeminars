-- DDL - Data Definition Language
-- CREATE, DROP, ALTER, TRUNCATE

-- DML
-- DCL
-- TCL

CREATE DATABASE HelloWorld
DROP TABLE "public"."student"

CREATE TABLE "public"."student"
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

ALTER TABLE "public"."student"
    ADD CONSTRAINT "UNQ__diploma_theme" UNIQUE("diploma_theme");

ALTER TABLE "public"."student"
    DROP CONSTRAINT "UNQ__diploma_theme"

ALTER TABLE "public"."student"
    ADD COLUMN "grade_book_number" VARCHAR NOT NULL DEFAULT('123456');

ALTER TABLE "public"."student"
    ADD CONSTRAINT "CHK_smth" CHECK ("course" BETWEEN 1 AND 5);

ALTER TABLE "public"."student"
    ADD CONSTRAINT "PK__grade_book_number" PRIMARY KEY("grade_book_number");

INSERT INTO "public"."student"
    VALUES ('Кешабян', 'Руслан', 'Русланович', DATE('02.05.2004'), TRUE, 3, 'мпм-122', 'тема диплома', '123460');

SELECT *
    FROM "public"."student"
    WHERE 1 = 1;

DELETE
    FROM "public"."student"
    WHERE 1 = 1
        AND grade_book_number LIKE '%123458%'