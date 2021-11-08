USE [DbMediator]

GO

CREATE TABLE [dbo].[regions]
(
	[id] INT NOT NULL PRIMARY KEY IDENTITY,
	[name] VARCHAR(100) NOT NULL
)

GO

INSERT INTO [dbo].[Regions]
  VALUES ('Russia'),
         ('USA'),
         ('England'),
         ('Zhumaisynba')