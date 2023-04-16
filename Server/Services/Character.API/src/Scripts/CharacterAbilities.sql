USE FightClubCharacterDB

CREATE TABLE CharacterAbilities(
	ID int IDENTITY(1, 1) PRIMARY KEY,
	CharacterID int NOT NULL FOREIGN KEY REFERENCES Characters(ID)
,	AbilityID int NOT NULL FOREIGN KEY REFERENCES Abilities(ID)
);

GO
