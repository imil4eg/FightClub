#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <iostream>

#include "Character.h"
#include "CharacterType.h"

class Player : public Character
{
public:
	Player(std::unique_ptr<Attributes> attributes, std::unique_ptr<Equipment> equipment, CharacterType characterType, std::unique_ptr<Weapon> weapon = {}) :
		Character{ std::move(attributes), std::move(equipment), characterType, std::move(weapon) }
	{
	}

	void playTurn(Character& target) override;

	void hit(Character& enemy, HitDirection hitDirection) override;
};

#endif // !PLAYER_H

