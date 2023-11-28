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

UPDATE public.students SET birthday = DATE '02.11.1955' WHERE record_book_number = '123-456'

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
  FROM public.teachers
SELECT *
  FROM public.students
  --WHERE name = 'Ivan' OR surname = 'Bryukin'
  WHERE surname LIKE '_i%'

CREATE TABLE public.teachers
(
    id INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
    surname TEXT NOT NULL,
    name TEXT NOT NULL,
    patronymic TEXT NULL,
    birthday DATE NOT NULL DEFAULT (DATE '01.01.2000'),
    academic_degree TEXT NULL,
    academic_title TEXT NULL
)

ALTER TABLE public.students
  ADD COLUMN scientific_adviser INT NULL DEFAULT(NULL)

ALTER TABLE public.students
  ADD CONSTRAINT FK__students_scientific_adviser__teachers_id FOREIGN KEY(scientific_adviser) REFERENCES public.teachers(id)

INSERT INTO public.teachers(surname, name, patronymic, birthday, academic_degree, academic_title)
  VALUES
    ('Petrov', 'Petr', 'Petrovich', DATE '01.31.1976', 'Ph.D in math', DEFAULT)

UPDATE public.students
  SET scientific_adviser = 1
    WHERE record_book_number = '123-456'

SELECT *
  FROM public.teachers
    CROSS JOIN public.teachers t

SELECT *
  FROM public.teachers
SELECT *
  FROM public.students

INSERT INTO public.teachers(surname, name, patronymic, birthday, academic_degree, academic_title)
  VALUES
    ('Kosarev', 'Andrew', 'Mikhailovich', DATE '09.23.1956', 'Ph.D in pravoslavie', 'Academic')

UPDATE public.students
  SET scientific_adviser = 2
    WHERE surname = 'Petrov'

SELECT t.surname AS teacher_surname,
       t.name AS teacher_name,
       count AS students_count
  FROM (SELECT scientific_adviser, COUNT(*) AS count
          FROM public.students s
            INNER JOIN public.teachers t
              ON s.scientific_adviser = t.id
          WHERE s.surname != 'Bryukin'
          GROUP BY scientific_adviser
            HAVING scientific_adviser != 1) AS sbqr
  INNER JOIN public.teachers t
    ON scientific_adviser = t.id

CREATE TABLE IF NOT EXISTS public.logs
(
    id INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
    text TEXT NOT NULL,
    date DATE DEFAULT now()
);

INSERT INTO public.logs(text) VALUES
('log example');

SELECT * FROM public.logs;


DROP FUNCTION f_trg_after_insert_student CASCADE;
CREATE FUNCTION f_trg_after_insert_student()
  RETURNS TRIGGER
  LANGUAGE plpgsql
AS $$
BEGIN
    INSERT INTO public.logs(text) VALUES
      (FORMAT('Inserted value into %s.%s: record_book_number = ''%s'', surname = ''%s'', name = ''%s'', patronymic = ''%s''',
          TG_TABLE_SCHEMA, TG_TABLE_NAME, NEW.record_book_number, NEW.surname, NEW.name, NEW.patronymic));

    RETURN NEW;
END;
$$;

CREATE TRIGGER trg_after_insert_student
  AFTER INSERT
  ON public.students
  FOR EACH ROW
  EXECUTE FUNCTION f_trg_after_insert_student();

DROP FUNCTION f_trg_after_update_student CASCADE;
CREATE FUNCTION f_trg_after_update_student()
  RETURNS TRIGGER
  LANGUAGE plpgsql
AS $$
BEGIN
    INSERT INTO public.logs(text) VALUES
      (FORMAT('Updated value into %s.%s: record_book_number = ''%s'', surname = ''%s'', name = ''%s'', patronymic = ''%s''',
          TG_TABLE_SCHEMA, TG_TABLE_NAME, NEW.record_book_number, NEW.surname, NEW.name, NEW.patronymic));

    RETURN NEW;
END;
$$;

CREATE TRIGGER trg_after_update_student
  AFTER UPDATE
  ON public.students
  FOR EACH ROW
  EXECUTE FUNCTION f_trg_after_update_student();

SELECT * from public.students;
SELECT * FROM public.logs;

INSERT INTO public.students (record_book_number, surname, name, patronymic, course) VALUES
  ('1337-1340', 'Bundin', 'Klim', 'Otetsovich', 3);
SELECT * FROM public.logs;

UPDATE public.students
  SET patronymic = 'Andreevich'
  WHERE name = 'Klim'