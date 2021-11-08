USE [DbMediator]

GO

CREATE TABLE [dbo].[users]
(
  [id] INT NOT NULL PRIMARY KEY IDENTITY,
  [login] VARCHAR(20) NOT NULL CHECK(LEN([login]) > 3),
  [password] BINARY(16) NOT NULL,
  [role_id] INT NOT NULL CHECK([role_id] BETWEEN 1 AND 2)
)

INSERT INTO [dbo].[users]
  VALUES ('login1', HASHBYTES('MD5', 'p1'), 1),
         ('login2', HASHBYTES('MD5', 'p2'), 2),
         ('login3', HASHBYTES('MD5', 'p3'), 2),
         ('login4', HASHBYTES('MD5', 'p4'), 2)