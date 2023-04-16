USE FightClubCharacterDB

CREATE TABLE Attributes(
	ID int IDENTITY(1, 1) PRIMARY KEY,
	Level int NOT NULL,
	Damage int NOT NULL,
	Strength int NOT NULL,
	Agility int NOT NULL
);

GO
