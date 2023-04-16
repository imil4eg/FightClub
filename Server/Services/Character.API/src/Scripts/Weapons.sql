USE FightClubCharacterDB

CREATE TABLE Weapons(
	ID int IDENTITY(1, 1) PRIMARY KEY,
	Name varchar(255) NOT NULL,
	Damage int NOT NULL
);

GO
