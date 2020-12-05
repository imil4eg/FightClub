#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "Character.h"
#include "CharacterType.h"

class Player : public Character
{
private:
	Player(Attributes* attributes, Equipment* equipment, CharacterType characterType, const Weapon* weapon = nullptr) :
		Character{ attributes, equipment, characterType, weapon }
	{
	}

public:
	friend class JsonGameDataProcesser;

	void playTurn(Character& target) override;

	void hit(Character& enemy, HitDirection hitDirection) override;
};

#endif // !PLAYER_H

