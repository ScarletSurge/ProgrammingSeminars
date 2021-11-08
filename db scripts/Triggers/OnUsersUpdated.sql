USE [DbMediator]

GO

CREATE TRIGGER [dbo].[trg_users_update]
  ON [dbo].[users]
  FOR UPDATE
AS
BEGIN

  DECLARE @deleted_user_id INT
  DECLARE @deleted_user_login VARCHAR(20)
  DECLARE @deleted_user_role_id INT
  DECLARE @inserted_user_id INT
  DECLARE @inserted_user_login VARCHAR(20)
  DECLARE @inserted_user_role_id INT

  DECLARE deleted_iterator CURSOR
    FOR SELECT [d].[id],
               [d].[login],
               [d].[role_id]
	    FROM deleted [d]

  DECLARE inserted_iterator CURSOR
    FOR SELECT [i].[id],
               [i].[login],
               [i].[role_id]
	    FROM inserted [i]

  OPEN deleted_iterator
  OPEN inserted_iterator

  FETCH NEXT
    FROM deleted_iterator
	INTO @deleted_user_id, @deleted_user_login, @deleted_user_role_id

  FETCH NEXT
    FROM inserted_iterator
	INTO @inserted_user_id, @inserted_user_login, @inserted_user_role_id

  WHILE (@@FETCH_STATUS = 0)
  BEGIN
    
	IF (@inserted_user_role_id != @deleted_user_role_id)
	BEGIN
      INSERT INTO [dbo].[logs]([description])
	    VALUES(CONCAT('User ', @inserted_user_login, ' role updated from ',
	      CASE @deleted_user_role_id
		    WHEN 1 THEN '"Admin"'
		    WHEN 2 THEN '"User"'
		    ELSE '"ROLE_UNDEFINED"'
			END, ' to ',
		  CASE @inserted_user_role_id
		    WHEN 1 THEN '"Admin"'
		    WHEN 2 THEN '"User"'
		    ELSE '"ROLE_UNDEFINED"'
		    END, '.'))
	END
  
    FETCH NEXT
      FROM deleted_iterator
	  INTO @deleted_user_id, @deleted_user_login, @deleted_user_role_id

    FETCH NEXT
      FROM inserted_iterator
	  INTO @inserted_user_id, @inserted_user_login, @inserted_user_role_id

  END
  
  CLOSE deleted_iterator
  DEALLOCATE deleted_iterator
  CLOSE inserted_iterator
  DEALLOCATE inserted_iterator
END