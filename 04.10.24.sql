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

INSERT INTO "public"."student"("grade_book_number", "name", "surname", "patronymic", "birth_date", "sex", "course", "group", "diploma_theme")
    VALUES ('123458', 'Кешабян', 'Руслан', 'Русланович', DATE('02.05.2004'), TRUE, 3, 'мпм-122', 'тема диплома'), ('123457', 'Забоев', 'Артём', 'Сергеевич', DATE('12.08.2004'), TRUE, 3, 'мпм-122', 'диплом not found :/');

INSERT INTO "public"."student"("name", "surname", "patronymic", "birth_date", "sex", "course", "group", "diploma_theme")
    VALUES ('Алпеева', 'Екатерина', 'Андреевна', DATE('03.01.2004'), FALSE, 3, 'мпм-122', 'тема диплома o_O')

SELECT * FROM "public"."student"

SELECT "s"."grade_book_number"
    FROM "public"."student" "s"
    WHERE 1 = 1;

-- CRUD

SELECT *
    FROM "public"."student"
    WHERE 1=1
        AND "surname" LIKE '%а%б%'

SELECT *
    FROM "public"."student";

DELETE
    FROM "public"."student"
    WHERE "name" LIKE '%аб%'

UPDATE "public"."student"
    SET "group" = 'мпм-123',
        "course" = 2
    WHERE "grade_book_number" = '123457'

SELECT *
    FROM "public"."student";

SELECT "course", COUNT(*)
    FROM "public"."student"
    GROUP BY "course"
        HAVING "course" != 2

SELECT *
    FROM "public"."student"
    ORDER BY "name" DESC