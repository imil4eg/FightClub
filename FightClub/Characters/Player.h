#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "Character.h"

class Player : public Character
{
public:
	Player(Attributes* const attributes, Equipment* const equipment, Weapon* weapon = nullptr) :
		Character{ attributes, equipment, weapon }
	{
	}

	void playTurn(Character& target) override;

	void hit(Character& enemy, HitDirection hitDirection) override;
};

#endif // !PLAYER_H

