#include "AttributesFactory.h"

std::unique_ptr<Attributes> AttributesFactory::create(const Weapon* const weapon, int level, int strength, int agility, CharacterType characterType)
{
	int totalStrength = strength + (m_levelAttributesBonus * level);
	int totalAgility = agility + (m_levelAttributesBonus * level);
	int weaponDamage = (weapon == nullptr) ? 0 : weapon->getDamage();
	int totalDamage = weaponDamage + m_defaultDamage + (((characterType == CharacterType::strong) ? strength : agility) * m_bonusDamageForMainAttributeMultiplier);
	int hp = m_defaultHp + (m_bonusHPForStrengthMultiplier * totalStrength);
	int stamina = m_defaultStamina + (m_staminaPerLevelBonus * level);

	return std::make_unique<Attributes>(hp, level, totalDamage, totalStrength, totalAgility, stamina);
}