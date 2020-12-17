#include "Battle/Battle.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			void FightPreparation(characters::Character& player, characters::Character& enemy)
			{
				player.restoreHp();
				enemy.restoreHp();
			}

			void Battle::fightWithBot(characters::Character& player)
			{
				auto bot{ m_botFactory->create(player) };

				m_messageDisplayer->display("The fighting beggins!\n\n");

				FightPreparation(player, bot);

				bool playerWon{};
				while (true)
				{
					player.playTurn(bot);

					if (bot.getAttributes()->getHp() <= 0)
					{
						playerWon = true;
						break;
					}

					bot.playTurn(player);

					if (player.getAttributes()->getHp() <= 0)
					{
						break;
					}
				}

				m_messageDisplayer->display(playerWon ? "You win!\n" : "You lost!\n");
			}
		}
	}
}