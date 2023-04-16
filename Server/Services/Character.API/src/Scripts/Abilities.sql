USE FightClubCharacterDB

CREATE TABLE Abilities(
	ID int IDENTITY(1, 1) PRIMARY KEY,
	Name varchar(255) NOT NULL,
	Cost int NOT NULL,
	Value int NOT NULL,
	Duration int NOT NULL,
	AbilityTypeID int NOT NULL FOREIGN KEY REFERENCES AbilityTypes(ID)
);

GO
