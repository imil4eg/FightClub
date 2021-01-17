#include "Battle/Fighters/FighterFactory.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			namespace fighters
			{
				struct FighterFactory::Impl
				{
					const io::IMessageDisplayer* m_messageDisplayer;
					const io::IInputProcesser* m_inputProcesser;
					const characterstuff::abilities::IAbilitiesDisplayer* m_abilitiesDisplayer;

					Impl(const io::IMessageDisplayer& messageDisplayer, const io::IInputProcesser& inputProcesser,
						 const characterstuff::abilities::IAbilitiesDisplayer& abilitiesDisplayer) : 
						m_messageDisplayer{ &messageDisplayer },
						m_inputProcesser{ &inputProcesser },
						m_abilitiesDisplayer{ &abilitiesDisplayer}
					{
					}

					~Impl() = default;
				};

				FighterFactory::FighterFactory(const io::IMessageDisplayer& messageDisplayer, const io::IInputProcesser& inputProcesser, 
					const characterstuff::abilities::IAbilitiesDisplayer& abilitiesDisplayer) :
					pImpl(std::make_unique<Impl>(messageDisplayer, inputProcesser, abilitiesDisplayer))
				{
				}

				FighterFactory::~FighterFactory() = default;

				std::unique_ptr<Fighter> FighterFactory::create(characters::Character& character) const
				{
					if (typeid(character) == typeid(characters::Player))
					{
						return std::make_unique<PlayerFighter>(*pImpl->m_messageDisplayer, *pImpl->m_inputProcesser, 
															    *pImpl->m_abilitiesDisplayer, character);
					}
					else
					{
						return std::make_unique<BotFighter>(*pImpl->m_messageDisplayer, character);
					}
				}
			}
		}
	}
}