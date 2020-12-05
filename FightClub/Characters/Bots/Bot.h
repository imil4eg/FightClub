#ifndef BOT_H
#define BOT_H

#include <memory>
#include <iostream>

#include "../../CharacterStuff/Attributes.h"
#include "../Character.h"
#include "../CharacterType.h"
#include "../../CharacterStuff/Equipment.h"
#include "../../CharacterStuff/Weapon.h"

class Bot : public Character
{
private:
	Bot(Attributes* const attributes, Equipment* const equipment, CharacterType characterType, Weapon* weapon = nullptr) :
		Character{ attributes, equipment, characterType, weapon }
	{
	}

	Bot(Character&& character) noexcept :
		Character{ std::move(character) }
	{
	}

public:
	friend class BotFactory;

	void playTurn(Character& player) override;
	void hit(Character& enemy, HitDirection hitDirection) override;
};

#endif // !BOT_H

