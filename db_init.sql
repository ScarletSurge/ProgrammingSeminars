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

-- INSERT SELECT UPDATE DELETE TRUNCATE

INSERT INTO public.students (record_book_number, surname, name, course) VALUES
  ('123-456', 'Ivanov', 'Ivan', 2),
  ('123-457', 'Petrov', 'Ivan', 2),
  ('123-458', 'Sidorov', 'Ivan', 2),
  ('123-459', 'Bryukin', 'Maxim', 3);

INSERT INTO public.students (record_book_number, surname, name, course) VALUES
  ('666-1337', 'Tryukina', 'Kryuksima', 4);

UPDATE public.students
  SET surname = 'Hryukina'
      -- ,name = '123'
  WHERE surname = 'Tryukina'


DELETE FROM public.students WHERE 1=1-- AND  OR

SELECT *
  FROM public.students s