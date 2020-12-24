#include <boost/algorithm/string.hpp>

#include "Battle/Fighters/PlayerFighter.h"
#include "Battle/DamageCalculator.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			namespace fighters
			{
				struct PlayerFighter::Impl
				{
					const io::IInputProcesser* m_inputProcesser;
					const io::IMessageDisplayer* m_messageDisplayer;

					Impl(const io::IMessageDisplayer& messageDisplayer, const io::IInputProcesser& inputProcesser) :
						m_messageDisplayer{ &messageDisplayer },
						m_inputProcesser{ &inputProcesser }
					{
					}

					battle::HitDirection askHitDirection()
					{
						while (true)
						{
							auto hitDirectionStr{ this->m_inputProcesser->getLine() };

							if (boost::iequals(hitDirectionStr, "head"))
							{
								return battle::HitDirection::head;
							}
							else if (boost::iequals(hitDirectionStr, "body"))
							{
								return battle::HitDirection::body;
							}
							else if (boost::iequals(hitDirectionStr, "legs"))
							{
								return battle::HitDirection::legs;
							}
							else
							{
								m_messageDisplayer->display("Entered not valid hit direction. Please, try again.\n\n");
							}
						}

						return battle::HitDirection::max_hit_direction;
					}

					~Impl() = default;
				};

				PlayerFighter::PlayerFighter(const io::IMessageDisplayer& messageDisplayer, const io::IInputProcesser& inputProcesser,
					characters::Character& player) :
					Fighter{messageDisplayer, player, "Player"},
					pImpl(std::make_unique<Impl>(messageDisplayer, inputProcesser))
				{
				}

				PlayerFighter::~PlayerFighter() = default;

				void PlayerFighter::playTurn(Fighter& target)
				{
					this->getMessageDisplayer().display("Your turn!\n\n");

					this->getMessageDisplayer().display("Choose where will you hit the opponen:\n1) Head\n2) Body\n3) Legs\n\n");

					battle::HitDirection hitDirection{ pImpl->askHitDirection() };

					Fighter::hit(target, hitDirection);
				}
			}
		}
	}
}