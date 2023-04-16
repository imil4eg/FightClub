CREATE DATABASE FightClubUserDB

GO

USE FightClubUserDB

CREATE TABLE Users (
	ID int IDENTITY(1, 1) PRIMARY KEY,
	UserName varchar(255) NOT NULL,
	Password varchar(255) NOT NULL
);

GO
