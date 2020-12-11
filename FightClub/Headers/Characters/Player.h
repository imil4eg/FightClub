#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <iostream>

#include "Character.h"
#include "CharacterType.h"
#include "CharacterStuff/Inventory.h"

class Player : public Character
{
private:
	std::unique_ptr<fightclub::characterstuff::Inventory> m_inventory{};

public:
	Player(std::unique_ptr<Attributes> attributes,
		   std::unique_ptr<Equipment> equipment,
		   CharacterType characterType,
		   std::unique_ptr<fightclub::characterstuff::Inventory> inventory,
		   std::unique_ptr<Weapon> weapon = {}) :
		Character{ std::move(attributes), std::move(equipment), characterType, std::move(weapon) },
		m_inventory{std::move(inventory)}
	{
	}

	Player(std::unique_ptr<Character>&& character, std::unique_ptr<fightclub::characterstuff::Inventory>&& inventory) : 
		Character{ std::move(character) },
		m_inventory{ std::move(inventory) }
	{
	}

	fightclub::characterstuff::Inventory& getInventory() { return *m_inventory.get(); }

	void playTurn(Character& target) override;

	void hit(Character& enemy, HitDirection hitDirection) override;
};

#endif // !PLAYER_H

