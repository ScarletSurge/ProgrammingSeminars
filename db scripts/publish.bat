set dbServer=localhost\SQLEXPRESS

sqlcmd -S %dbServer% -i .\Db\Init.sql
sqlcmd -S %dbServer% -i .\Tables\Users.sql
sqlcmd -S %dbServer% -i .\Tables\Regions.sql
sqlcmd -S %dbServer% -i .\Tables\Target.sql
sqlcmd -S %dbServer% -i .\Tables\Logs.sql
sqlcmd -S %dbServer% -i .\Queries\Authorize.sql
sqlcmd -S %dbServer% -i .\Queries\GetTarget.sql
sqlcmd -S %dbServer% -i .\Queries\GetRegions.sql
sqlcmd -S %dbServer% -i .\Queries\GetUsers.sql
sqlcmd -S %dbServer% -i .\Queries\UpdateUser.sql
sqlcmd -S %dbServer% -i .\Queries\GetLogs.sql
sqlcmd -S %dbServer% -i .\Triggers\OnUsersUpdated.sql