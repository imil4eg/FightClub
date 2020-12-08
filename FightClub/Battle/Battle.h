#ifndef BATTLE_H
#define BATTLE_H

#include <memory>

#include "../Characters/Bots/IBotFactory.h"
#include "../Characters/Character.h"
#include "IBattle.h"

class Battle : public IBattle
{
private:
	IBotFactory* m_botFactory;

public:
	Battle(IBotFactory* botFactory) : m_botFactory{ botFactory }
	{
	}

	void fightWithBot(Character& player) override;
};

#endif // !BATTLE_H

