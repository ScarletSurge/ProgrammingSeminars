USE [DbMediator]

GO

CREATE PROCEDURE [dbo].[sp_get_logs]
AS
BEGIN

  SELECT [l].[id],
         [l].[description],
		 [l].[created],
		 [u].[login]
    FROM [dbo].[logs] [l]
	  LEFT JOIN [dbo].[users] [u]
	    ON [l].[owner_id] = [u].[id]

  RETURN 0

END