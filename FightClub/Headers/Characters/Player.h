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
	const Weapon* m_weapon;

public:
	Player(std::unique_ptr<Attributes> attributes,
		   std::unique_ptr<Equipment> equipment,
		   CharacterType characterType,
		   std::unique_ptr<fightclub::characterstuff::Inventory> inventory,
		   const Weapon* weapon = nullptr) :
		Character{ std::move(attributes), std::move(equipment), characterType},
		m_inventory{std::move(inventory)},
		m_weapon{weapon}
	{
	}

	Player(std::unique_ptr<Character>&& character, std::unique_ptr<fightclub::characterstuff::Inventory>&& inventory, const Weapon* weapon) : 
		Character{ std::move(character) },
		m_inventory{ std::move(inventory) },
		m_weapon{weapon}
	{
	}

	fightclub::characterstuff::Inventory& getInventory() { return *m_inventory.get(); }

	void playTurn(Character& target) override;
	void hit(Character& enemy, HitDirection hitDirection) override;
	const Weapon* const getWeapon() const override { return m_weapon; }
	void changeWeapon(std::unique_ptr<Weapon> weapon);
};

#endif // !PLAYER_H

