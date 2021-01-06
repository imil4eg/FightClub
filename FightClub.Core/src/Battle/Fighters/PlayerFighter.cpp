#include <boost/algorithm/string.hpp>
#include <string>

#include "Battle/Fighters/PlayerFighter.h"
#include "Battle/DamageCalculator.h"
#include "CharacterStuff/BodyPart.h"

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
					const std::string HeadText{ "Head" };
					const std::string BodyText{ "Body" };
					const std::string LegsText{ "Legs" };

					const io::IInputProcesser* m_inputProcesser;
					const io::IMessageDisplayer* m_messageDisplayer;

					Impl(const io::IMessageDisplayer& messageDisplayer, const io::IInputProcesser& inputProcesser) :
						m_messageDisplayer{ &messageDisplayer },
						m_inputProcesser{ &inputProcesser }
					{
					}

					characterstuff::BodyPart askBodyPart()
					{
						while (true)
						{
							auto hitDirectionStr{ this->m_inputProcesser->getLine() };

							if (boost::iequals(hitDirectionStr, HeadText))
							{
								return characterstuff::BodyPart::head;
							}
							else if (boost::iequals(hitDirectionStr, BodyText))
							{
								return characterstuff::BodyPart::body;
							}
							else if (boost::iequals(hitDirectionStr, LegsText))
							{
								return characterstuff::BodyPart::legs;
							}
							else
							{
								m_messageDisplayer->display("Entered not valid hit direction. Please, try again.\n\n");
							}
						}

						return characterstuff::BodyPart::max_body_part;
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

				void PlayerFighter::askDecisions()
				{
					this->getMessageDisplayer().display("Your turn!\n\n");

					this->getMessageDisplayer().display("Choose where will you hit the opponent:\n1) " + pImpl->HeadText +
						"\n2) " + pImpl->BodyText + "\n3) " + pImpl->LegsText + "\n\n");

					characterstuff::BodyPart hitDirection{ pImpl->askBodyPart() };

					this->setHitDirection(hitDirection);

					this->getMessageDisplayer().display("Choose which part of your character will you protect:\n1) " + pImpl->HeadText +
						"\n2) " + pImpl->BodyText + "\n3) " + pImpl->LegsText + "\n\n");

					characterstuff::BodyPart protectDirection{ pImpl->askBodyPart() };

					this->setProtectingPart(protectDirection);
				}
			}
		}
	}
}