USE FightClubCharacterDB

CREATE TABLE Characters(
	ID int IDENTITY(1, 1) PRIMARY KEY,
	CharacterType int NOT NULL,
	UserID int NOT NULL,
	AttributeID int NOT NULL,
	HeadID int,
	CuirassID int,
	BootsID int,
	WeaponID int
);

GO
