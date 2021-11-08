USE [DbMediator]

GO

CREATE PROCEDURE [dbo].[sp_authorize]
(
  @login VARCHAR(20),
  @password BINARY(16),
  @authorized INT OUT,
  @role_id INT OUT
)
AS
BEGIN

-- TODO: input parameters validation

  IF NOT EXISTS(SELECT 1
                  FROM [dbo].[users] [u]
				  WHERE @login = [u].[login])
  BEGIN
    SET @authorized = 1
	INSERT INTO [dbo].[logs]([description])
	  VALUES(CONCAT('Authorization failed (login ', @login , ' not found)!'))
	RETURN 0
  END

  DECLARE @user_id INT
  DECLARE @user_password_hash BINARY(16)

  SELECT @user_id = [u].[id],
         @user_password_hash = [u].[password],
		 @role_id = [u].[role_id]
    FROM [dbo].[users] [u]
	WHERE @login = [u].[login]

  IF @user_password_hash != @password
  BEGIN
    SET @authorized = 2
	INSERT INTO [dbo].[logs]([description], [owner_id])
	  VALUES('Authorization failed (invalid password)!', @user_id)
	RETURN 0
  END

  INSERT INTO [dbo].[logs]([description], [owner_id])
	VALUES('Authorization succeeded.', @user_id)

  SET @authorized = 0

  RETURN 0

END