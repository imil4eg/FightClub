#include <vector>
#include <utility>
#include <queue>

#include "Battle/Fighters/Fighter.h"
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
				struct Fighter::Impl
				{
					const io::IMessageDisplayer* m_messageDisplayer;
					const characters::Character* m_character;
					const std::string m_characterName;
					characterstuff::BodyPart m_protectingPart;
					characterstuff::BodyPart m_hitDirection;
					const abils::Ability* m_usedAbility;
					int m_leftStamina;
					int m_leftHP;
					std::vector<buffWithDuration_t> m_buffs;
					std::queue<const abils::Ability*> m_traps;

					Impl(const io::IMessageDisplayer& messageDisplayer, const characters::Character& character, const std::string characterName) : 
						m_messageDisplayer{&messageDisplayer},
						m_character{ &character },
						m_characterName{ characterName },
						m_protectingPart{characterstuff::BodyPart::max_body_part},
						m_hitDirection{characterstuff::BodyPart::max_body_part},
						m_usedAbility{},
						m_leftStamina{character.getAttributes()->getStamina()},
						m_leftHP{character.getAttributes()->getHp()},
						m_traps{},
						m_buffs{}
					{
					}

					~Impl() = default;

					void decreaseBuffs()
					{
						for (int i{static_cast<int>(m_buffs.size()) - 1}; i >= 0; --i)
						{
							--m_buffs[i].second;

							if (m_buffs[i].second == 0)
								m_buffs.erase(m_buffs.begin() - i);
						}
					}

					void useEnemyTrap(const Fighter& target)
					{
						if (!m_traps.size())
						{
							return;
						}

						auto trap{ m_traps.front() }; m_traps.pop();

						std::cout << target.pImpl->m_characterName << " got into trap and hit back on " + std::to_string(trap->getValue()) 
								  << " damage.\n";

						m_leftHP -= trap->getValue();
					}

					void updateDurationOrPushBackBoost(const abils::Ability* ability)
					{
						auto abilityIt{ std::find_if(m_buffs.begin(), m_buffs.end(), 
							[&](const std::pair<const abils::Ability*, int> buff)
							{
								return buff.first->getId() == ability->getId();
							}) };

						if (abilityIt == m_buffs.end())
						{
							buffWithDuration_t buffWithDuration{ ability, ability->getDuration() };
							m_buffs.push_back(buffWithDuration);
						}
						else
						{
							abilityIt->second = ability->getDuration();
						}
					}
				};

				Fighter::Fighter(const io::IMessageDisplayer& messageDisplayer, const characters::Character& character, const std::string characterName) :
					pImpl(std::make_unique<Impl>(messageDisplayer, character, characterName))
				{
				}

				Fighter::~Fighter() = default;

				const io::IMessageDisplayer& Fighter::getMessageDisplayer() const { return *pImpl->m_messageDisplayer; }
				const characters::Character& Fighter::getCharacter() const { return *pImpl->m_character; }
				const std::vector<Fighter::buffWithDuration_t>& Fighter::getBuffs() const { return pImpl->m_buffs; }
				int Fighter::getLeftStamina() const { return pImpl->m_leftStamina; }
				void Fighter::setProtectingPart(characterstuff::BodyPart bodyPart) { pImpl->m_protectingPart = bodyPart; }
				void Fighter::setHitDirection(characterstuff::BodyPart hitDirection) { pImpl->m_hitDirection = hitDirection; }
				void Fighter::setUsedSpell(const abils::Ability* ability) 
				{ 
					pImpl->m_usedAbility = ability;

					if (ability == nullptr)
						return;

					pImpl->m_leftStamina -= ability->getCost();
					switch (ability->getType())
					{
					case abils::AbilityType::trap:
						pImpl->m_traps.push(ability);
						break;
					case abils::AbilityType::armor_boost:
					case abils::AbilityType::damage_boost:
						pImpl->updateDurationOrPushBackBoost(ability);
						break;
					}
				}

				bool Fighter::isDead()
				{
					return pImpl->m_leftHP <= 0;
				}

				void Fighter::playTurn(Fighter& target)
				{
					int damage = battle::DamageCalculator::Calculate(*this->pImpl->m_character, *target.pImpl->m_character, 
																	 pImpl->m_hitDirection, target.pImpl->m_protectingPart, 
																     pImpl->m_buffs, target.pImpl->m_buffs);

					pImpl->m_messageDisplayer->display(pImpl->m_characterName + " hits " + target.pImpl->m_characterName + " to " + pImpl->m_hitDirection +
						" no " + std::to_string(damage) + " damage.\n");

					target.pImpl->m_leftHP -= damage;

					pImpl->useEnemyTrap(target);

					pImpl->m_messageDisplayer->display(target.pImpl->m_characterName + " HP: " +
						std::to_string(target.pImpl->m_leftHP));
				
					pImpl->decreaseBuffs();
				}
			}
		}
	}
}