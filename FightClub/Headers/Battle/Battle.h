#ifndef BATTLE_H
#define BATTLE_H

#include <memory>

#include "../Characters/Bots/IBotFactory.h"
#include "../Characters/Character.h"
#include "IBattle.h"

namespace fightclub
{
	namespace battle
	{
		class Battle : public IBattle
		{
		private:
			characters::bots::IBotFactory* m_botFactory;

		public:
			Battle(characters::bots::IBotFactory* botFactory) : m_botFactory{ botFactory }
			{
			}

			void fightWithBot(characters::Character& player) override;
		};

	}
}

#endif // !BATTLE_H

