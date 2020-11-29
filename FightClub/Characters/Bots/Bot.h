#ifndef BOT_H
#define BOT_H

#include <iostream>

#include "../../CharacterStuff/Attributes.h"
#include "../Character.h"
#include "../../CharacterStuff/Equipment.h"
#include "../../CharacterStuff/Weapon.h"

class Bot : public Character
{
public:
	Bot(Attributes* const attributes, Equipment* const equipment, Weapon* const weapon = nullptr) :
		Character{ attributes, equipment, weapon }
	{
	}

	Bot(Bot&& bot) noexcept :
		Character{ bot.getAttributes(), bot.getEquipment(), bot.getWeapon() }
	{
	}

	void playTurn(Character& player) override;
	void hit(Character& enemy, HitDirection hitDirection) override;
};

#endif // !BOT_H

