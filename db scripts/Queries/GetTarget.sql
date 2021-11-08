USE [DbMediator]

GO

CREATE PROCEDURE [dbo].[sp_get_target]
(
  @region_id INT
)
AS
BEGIN

  SELECT [t].[id],
		 [t].[login],
		 [t].[name],
		 [t].[surname],
		 [t].[birth_date],
		 [r].[name] as [region]
    FROM [dbo].[target] [t]
	  INNER JOIN [dbo].[regions] [r]
	    ON [t].[region_id] = [r].[id]
	  WHERE [t].[region_id] = @region_id
		OR @region_id = 0

  RETURN 0

END