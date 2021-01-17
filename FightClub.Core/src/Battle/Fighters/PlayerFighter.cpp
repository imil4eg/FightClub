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
					const std::string SkipCommandText{ "skip" };

					const io::IInputProcesser* m_inputProcesser;
					const io::IMessageDisplayer* m_messageDisplayer;
					const abils::IAbilitiesDisplayer* m_abilityDisplayer;

					Impl(const io::IMessageDisplayer& messageDisplayer, 
						const io::IInputProcesser& inputProcesser,
						const abils::IAbilitiesDisplayer& abilityDisplayer) :
						m_messageDisplayer{ &messageDisplayer },
						m_inputProcesser{ &inputProcesser },
						m_abilityDisplayer{&abilityDisplayer}
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

					void displayCurrentBuffs(const std::vector<Fighter::buffWithDuration_t>& buffs)
					{
						m_messageDisplayer->display("Current buffs:");

						if (buffs.size())
						{
							for (auto it{ buffs.begin() }; it != buffs.end(); ++it)
							{
								const auto* ability{ it->first };
								m_messageDisplayer->display("Name: " + ability->getName() + " Value: " + std::to_string(ability->getValue())
									+ " Duration: " + std::to_string(it->second) + '\n');
							}
						}
						else
						{
							m_messageDisplayer->display("No buffs.\n");
						}
					}

					const abils::Ability* askAbility(const abils::AbilitiesContainer& container, int leftStamina)
					{
						while (true)
						{
							m_abilityDisplayer->showSelected(container);

							m_messageDisplayer->display("You have " + std::to_string(leftStamina) + " stamina left.\n");

							m_messageDisplayer->display("Enter name of an ability that you want to use or enter " +
									SkipCommandText + ".\n");

							auto abilityName{ m_inputProcesser->getLine() };

							if (boost::iequals(abilityName, SkipCommandText))
							{
								return nullptr;
							}

							auto abilityIt{ container.find(abilityName) };

							if (abilityIt == container.getSelected().end())
							{
								std::cout << "Incorrect ability name was entered. Please, try again.\n";
							}
							else if ((*abilityIt)->getCost() > leftStamina)
							{
								std::cout << "Not enough stamina to use selected ability. Please, try again.\n";
							}
							else
							{
								return *abilityIt;
							}
						}
					}

					~Impl() = default;
				};

				PlayerFighter::PlayerFighter(const io::IMessageDisplayer& messageDisplayer, 
					const io::IInputProcesser& inputProcesser,
					const abils::IAbilitiesDisplayer& abilityDisplayer,
					characters::Character& player) :
					Fighter{messageDisplayer, player, "Player"},
					pImpl(std::make_unique<Impl>(messageDisplayer, inputProcesser, abilityDisplayer))
				{
				}

				PlayerFighter::~PlayerFighter() = default;

				void PlayerFighter::askDecisions()
				{
					this->getMessageDisplayer().display("Your turn!\n\n");

					pImpl->displayCurrentBuffs(this->getBuffs());

					auto ability{ pImpl->askAbility(this->getCharacter().getAbilitiesContainer(), this->getLeftStamina()) };

					this->setUsedSpell(ability);

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