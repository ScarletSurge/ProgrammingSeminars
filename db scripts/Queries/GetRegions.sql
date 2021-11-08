USE [DbMediator]

GO

CREATE PROCEDURE [dbo].[sp_get_regions]
AS
BEGIN

  SELECT *
    FROM [dbo].[regions]

  RETURN 0

END