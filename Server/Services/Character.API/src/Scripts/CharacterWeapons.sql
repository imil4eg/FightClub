USE FightClubCharacterDB

CREATE TABLE CharacterWeapons(
	ID int IDENTITY(1, 1) PRIMARY KEY,
	CharacterID int NOT NULL FOREIGN KEY REFERENCES Characters(ID),
	WeaponID int NOT NULL FOREIGN KEY REFERENCES Weapons(ID)
);

GO
