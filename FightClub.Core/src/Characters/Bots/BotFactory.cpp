#include "Characters/Bots/BotFactory.h"
#include "Common/RandomGenerator.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			namespace bots
			{
				void BotFactory::calculateAttributeValueToAdd(int& attributeValueToIncrease, int& attribueteValueToDecrease)
				{
					int possibleValueToExchange{ attribueteValueToDecrease - ((attribueteValueToDecrease < m_attributeDependOnTypeExchangeValue) ? m_minAttributeValue : m_attributeDependOnTypeExchangeValue) };

					attributeValueToIncrease += possibleValueToExchange;
					attribueteValueToDecrease -= possibleValueToExchange;
				}

				void BotFactory::calculateAttributes(int& strength, int& agility, CharacterType botCharacterType)
				{
					switch (botCharacterType)
					{
					case CharacterType::strong:
					{
						calculateAttributeValueToAdd(strength, agility);
						break;
					}
					case CharacterType::smooth:
						calculateAttributeValueToAdd(agility, strength);
						break;
					default:
						throw std::out_of_range("Not implemented CharacterType.");
					}
				}

				Bot BotFactory::create(const Character& player)
				{
					auto botCharacterType{ static_cast<CharacterType>(common::RandomGenerator::getBetween(0, static_cast<int>(CharacterType::max_character_type) - 1)) };

					int strength = player.getAttributes()->getStrength();
					int agility = player.getAttributes()->getAgility();

					calculateAttributes(strength, agility, botCharacterType);

					auto weapon{ m_weaponStorage->getRandomWeapon() };

					auto botAttributes{ m_attributeFactory->create(weapon.get(), player.getAttributes()->getLevel(), strength, agility, botCharacterType) };

					auto head{ m_armorStorage->getRandom(characterstuff::armors::ArmorType::head) };
					auto cuirasse{ m_armorStorage->getRandom(characterstuff::armors::ArmorType::body) };
					auto boots{ m_armorStorage->getRandom(characterstuff::armors::ArmorType::legs) };
					auto equipment{ std::make_unique<characterstuff::StaticEquipment>(std::move(head), std::move(cuirasse), std::move(boots)) };

					return Bot{ std::move(botAttributes), std::move(equipment), botCharacterType, std::move(weapon) };
				}
			}
		}
	}
}