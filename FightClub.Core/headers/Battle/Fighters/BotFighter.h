#pragma once

#include "Fighter.h"
#include "Characters/Bots/Bot.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			namespace fighters
			{
				class BotFighter : public Fighter
				{
				public:
					BotFighter(io::IMessageDisplayer& messageDisplayer, characters::Character& bot) :
						Fighter(messageDisplayer, bot, "Enemy")
					{
					}

					void playTurn(Fighter& target) override;
				};
			}
		}
	}
}