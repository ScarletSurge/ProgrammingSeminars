USE [DbMediator]

GO

CREATE PROCEDURE [dbo].[sp_get_users]
AS
BEGIN
  
  SELECT [u].[id],
         [u].[login],
		 [u].[role_id]
    FROM [dbo].[users] [u]

  RETURN 0

END