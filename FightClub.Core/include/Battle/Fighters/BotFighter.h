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
				private:
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					BotFighter(const io::IMessageDisplayer& messageDisplayer, const characters::Character& bot);
					~BotFighter();

					void askDecisions() override;
				};
			}
		}
	}
}