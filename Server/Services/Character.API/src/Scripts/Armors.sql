USE FightClubCharacterDB

CREATE TABLE Armors(
	ID int IDENTITY(1, 1) PRIMARY KEY,
	AttributeID int NOT NULL FOREIGN KEY REFERENCES Attributes(ID),
	ArmorTypeID int NOT NULL FOREIGN KEY REFERENCES ArmorTypes(ID),
	Name varchar(255) NOT NULL,
	Armor int NOT NULL
);

GO
