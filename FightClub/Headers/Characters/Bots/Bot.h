#ifndef BOT_H
#define BOT_H

#include <memory>
#include <iostream>

#include "../../CharacterStuff/Attributes.h"
#include "../Character.h"
#include "../CharacterType.h"
#include "../../CharacterStuff/Equipment.h"
#include "../../CharacterStuff/Weapons/Weapon.h"

class Bot : public Character
{
private:
	std::unique_ptr<Weapon> m_weapon;

public:
	Bot(std::unique_ptr<Attributes> attributes, std::unique_ptr<Equipment> equipment, CharacterType characterType, std::unique_ptr<Weapon> weapon = {}) :
		Character{ std::move(attributes), std::move(equipment), characterType },
		m_weapon{std::move(weapon)}
	{
	}

	Bot(Bot&& bot) :
		Character{ std::move(bot) },
		m_weapon{std::move(bot.m_weapon) }
	{
	}

	void playTurn(Character& player) override;
	void hit(Character& enemy, HitDirection hitDirection) override;
	const Weapon* const getWeapon() const override { return m_weapon.get(); }
};

#endif // !BOT_H

