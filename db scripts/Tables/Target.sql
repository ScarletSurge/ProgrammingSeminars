USE [DbMediator]

GO

CREATE TABLE [dbo].[target]
(
	[id] INT NOT NULL PRIMARY KEY IDENTITY,
	[login] VARCHAR(20) NOT NULL UNIQUE CHECK(LEN([login]) >= 4),
	[surname] VARCHAR(40) NOT NULL,
	[name] VARCHAR(40) NOT NULL,
	[birth_date] DATE NOT NULL CHECK([birth_date] <= GETDATE()),
    [region_id] INT NOT NULL FOREIGN KEY REFERENCES [dbo].[regions] ([id]),
	CHECK(LEN([surname]) != 0 AND LEN([name]) != 0)
)

GO

INSERT INTO [dbo].[target]
  VALUES ('login1', 'Ivanov', 'Alexey', GETDATE(), 1)
       , ('login2', 'Petrov', 'Roman', GETDATE(), 2)
       , ('login3', 'Makarov', 'Kirill', GETDATE(), 3)
       , ('login4', 'Yuldashev', 'Andrew', GETDATE(), 4)
	   , ('login5', 'Vasil''ev', 'Dmitry', GETDATE(), 1)
       , ('login6', 'Pechenina', 'Katherine', GETDATE(), 2)
       , ('login7', 'Makhmudova', 'Ilzara', GETDATE(), 3)
       , ('login8', 'Rizoev', 'Bah', GETDATE(), 4)