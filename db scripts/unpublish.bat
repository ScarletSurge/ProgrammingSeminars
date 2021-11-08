set dbServer=localhost\SQLEXPRESS

sqlcmd -S %dbServer% -i .\Db\Drop.sql