CREATE DATABASE HelloWorld

CREATE TABLE public.students
(
    record_book_number TEXT NOT NULL PRIMARY KEY, -- AUTOINCREMENT
    surname TEXT NOT NULL,
    name TEXT NOT NULL,
    patronymic TEXT NULL,
    birthday DATE NOT NULL DEFAULT (DATE '01.01.2000'),
    -- state INT NOT NULL,
    course INT CHECK (course >= 1 AND course <= 4)
)

DROP TABLE public.students

ALTER TABLE public.students
    ADD COLUMN faq TEXT NOT NULL DEFAULT ('Unknown')
