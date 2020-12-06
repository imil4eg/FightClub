#include <exception>
#include <memory>

#include "BotFactory.h"
#include "../CharacterType.h"
#include "../../Common/RandomGenerator.h"

void BotFactory::calculateAttributeValueToAdd(int& attributeValueToIncrease, int& attribueteValueToDecrease)
{
	int possibleValueToExchange{ attribueteValueToDecrease - ((attribueteValueToDecrease < m_attributeDependOnTypeExchangeValue) ? m_minAttributeValue : m_attributeDependOnTypeExchangeValue )};
	
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
	auto botCharacterType{ static_cast<CharacterType>(RandomGenerator::getBetween(0, static_cast<int>(CharacterType::max_character_type) - 1)) };

	int strength = player.getAttributes()->getStrength();
	int agility = player.getAttributes()->getAgility();

	calculateAttributes(strength, agility, botCharacterType);

	Weapon* weapon{ m_weaponStorage->getRandomWeapon() };
	 
	auto botAttributes{ m_attributeFactory->create(weapon, player.getAttributes()->getLevel(), strength, agility, botCharacterType) };
	
	auto head{ m_armorStorage->getRandom(Armor::Type::head) };
	auto cuirasse{ m_armorStorage->getRandom(Armor::Type::body) };
	auto boots{ m_armorStorage->getRandom(Armor::Type::legs) };
	Equipment equipment{ head, cuirasse, boots };

	 return Bot{ &botAttributes, &equipment, botCharacterType, weapon };
}
