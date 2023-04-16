#include "Battle/Fighters/BotFighter.h"
#include "Common/RandomGenerator.h"
#include "CharacterStuff/BodyPart.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			namespace fighters
			{
				struct BotFighter::Impl
				{
					Impl() = default;
					~Impl() = default;

					const characterstuff::abilities::Ability* getRandomAbility(const characterstuff::abilities::AbilitiesContainer& container, 
																				int leftStamina)
					{
						const auto& selectedAbilitiesContainer{ container.getSelected() };

						int abilityIndex{ common::RandomGenerator::getBetween(0, selectedAbilitiesContainer.size() - 1) };
						const auto* ability{ selectedAbilitiesContainer[abilityIndex] };

						return  (ability == nullptr || ability->getCost() > leftStamina) ? nullptr : ability;
					}
				};

				BotFighter::BotFighter(const io::IMessageDisplayer& messageDisplayer, const characters::Character& bot) :
					Fighter(messageDisplayer, bot, "Enemy"),
					pImpl(std::make_unique<Impl>())
				{
				}

				BotFighter::~BotFighter() = default;

				void BotFighter::askDecisions()
				{
					this->getMessageDisplayer().display("Enemy turn!\n\n");

					this->setUsedSpell(pImpl->getRandomAbility(this->getCharacter().getAbilitiesContainer(), this->getLeftStamina()));

					auto hitDirection{ static_cast<characterstuff::BodyPart>(
						common::RandomGenerator::getBetween(0, static_cast<int>(characterstuff::BodyPart::max_body_part) - 1)) };

					this->setHitDirection(hitDirection);

					auto protectingPart{ static_cast<characterstuff::BodyPart>(
						common::RandomGenerator::getBetween(0, static_cast<int>(characterstuff::BodyPart::max_body_part) - 1)) };
				
					this->setProtectingPart(protectingPart);
				}
			}
		}
	}
}