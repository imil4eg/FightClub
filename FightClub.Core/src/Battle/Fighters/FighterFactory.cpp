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

					Impl(const io::IMessageDisplayer& messageDisplayer, const io::IInputProcesser& inputProcesser) : 
						m_messageDisplayer{ &messageDisplayer },
						m_inputProcesser{ &inputProcesser }
					{
					}

					~Impl() = default;
				};

				FighterFactory::FighterFactory(const io::IMessageDisplayer& messageDisplayer, const io::IInputProcesser& inputProcesser) :
					pImpl(std::make_unique<Impl>(messageDisplayer, inputProcesser))
				{
				}

				FighterFactory::~FighterFactory() = default;

				std::unique_ptr<Fighter> FighterFactory::create(characters::Character& character) const
				{
					if (typeid(character) == typeid(characters::Player))
					{
						return std::make_unique<PlayerFighter>(*pImpl->m_messageDisplayer, *pImpl->m_inputProcesser, character);
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