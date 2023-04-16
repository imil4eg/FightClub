USE FightClubCharacterDB

CREATE TABLE CharacterArmors(
	ID int IDENTITY(1, 1) PRIMARY KEY,
	CharacterID int NOT NULL,
	ArmorID int NOT NULL
);

GO
