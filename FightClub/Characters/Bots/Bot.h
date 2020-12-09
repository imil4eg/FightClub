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
public:
	Bot(std::unique_ptr<Attributes> attributes, std::unique_ptr<Equipment> equipment, CharacterType characterType, std::unique_ptr<Weapon> weapon = {}) :
		Character{ std::move(attributes), std::move(equipment), characterType, std::move(weapon) }
	{
	}

	Bot(Bot&& bot) :
		Character{ std::move(bot) }
	{
	}

	void playTurn(Character& player) override;
	void hit(Character& enemy, HitDirection hitDirection) override;
};

#endif // !BOT_H

