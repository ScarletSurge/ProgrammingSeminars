USE [DbMediator]

GO

CREATE PROCEDURE [dbo].[sp_update_user]
(
  @user_id INT,
  @role_id INT
)
AS
BEGIN

  UPDATE [dbo].[users]
    SET [role_id] = @role_id
	WHERE @user_id = [id]

  RETURN 0

END