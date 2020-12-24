#include "Battle/Battle.h"
#include "Characters/Player.h"
#include "Characters/Character.h"
#include "Common/RandomGenerator.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			struct Battle::Impl
			{
				characters::bots::IBotFactory* m_botFactory;
				fighters::IFighterFactory* m_fighterFactory;
				io::IMessageDisplayer* m_messageDisplayer;

			public:
				Impl(characters::bots::IBotFactory& botFactory, fighters::IFighterFactory& fighterFactory,
					 io::IMessageDisplayer& messageDisplayer) : 
					m_botFactory{&botFactory},
					m_fighterFactory{ &fighterFactory },
					m_messageDisplayer{ &messageDisplayer }
				{
				}

				~Impl() = default;
			};

			Battle::Battle(characters::bots::IBotFactory& botFactory, fighters::IFighterFactory& fighterFactory,
				io::IMessageDisplayer& messageDisplayer) :
				pImpl(std::make_unique<Impl>(botFactory, fighterFactory, messageDisplayer))
			{
			}

			Battle::~Battle() = default;

			void FightPreparation(characters::Character& player, characters::Character& enemy)
			{
				player.restoreHp();
				enemy.restoreHp();
			}

			void Battle::fightWithBot(characters::Character& player)
			{
				auto bot{ pImpl->m_botFactory->create(player) };

				auto botFighter{ pImpl->m_fighterFactory->create(bot) };
				auto playerFighter{ pImpl->m_fighterFactory->create(player) };

				FightPreparation(player, bot);

				bool playerWon{};
				while (true)
				{
					playerFighter->playTurn(*botFighter.get());

					if (bot.getAttributes()->getHp() <= 0)
					{
						playerWon = true;
						break;
					}

					botFighter->playTurn(*playerFighter.get());

					if (player.getAttributes()->getHp() <= 0)
					{
						break;
					}
				}

				pImpl->m_messageDisplayer->display(playerWon ? "You win!\n" : "You lost!\n");
			}
		}
	}
}