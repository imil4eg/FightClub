#pragma once

#include "Characters/Player.h"
#include "Battle/Fighters/BotFighter.h"
#include "Battle/Fighters/PlayerFighter.h"
#include "IO/IMessageDisplayer.h"
#include "IO/IInputProcesser.h"
#include "IFighterFactory.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			namespace fighters
			{
				class FighterFactory : public IFighterFactory
				{
				private:
					const io::IMessageDisplayer* m_messageDisplayer;
					const io::IInputProcesser* m_inputProcesser;

				public:
					FighterFactory(const io::IMessageDisplayer& messageDisplayer, const io::IInputProcesser& inputProcesser) : 
						m_messageDisplayer{ &messageDisplayer },
						m_inputProcesser{ &inputProcesser }
					{
					}

					std::unique_ptr<Fighter> create(characters::Character& character) const override
					{
						if (typeid(character) == typeid(characters::Player))
						{
							return std::make_unique<PlayerFighter>(m_messageDisplayer, m_inputProcesser, character);
						}
						else
						{
							return std::make_unique<BotFighter>(m_messageDisplayer, character);
						}
					}
				};
			}
		}
	}
}