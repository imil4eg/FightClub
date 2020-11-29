#ifndef BATTLE_H
#define BATTLE_H

#include <memory>

#include "../Characters/Bots/IBotFactory.h"
#include "../Characters/Character.h"
#include "IBattle.h"

class Battle : public IBattle
{
private:
	const std::shared_ptr<IBotFactory> m_botFactory;

public:
	Battle(const std::shared_ptr<IBotFactory> botFactory) : m_botFactory{ botFactory }
	{
	}

	void fightWithBot(Character& player) override;
};

#endif // !BATTLE_H

