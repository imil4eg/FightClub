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
					BotFighter(const io::IMessageDisplayer& messageDisplayer, const characters::Character& bot) :
						Fighter(messageDisplayer, bot, "Enemy")
					{
					}

					void askDecisions() override;
				};
			}
		}
	}
}