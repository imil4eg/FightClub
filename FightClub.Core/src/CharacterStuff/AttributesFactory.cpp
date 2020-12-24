#include "CharacterStuff/AttributesFactory.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			struct AttributesFactory::Impl
			{
				const int m_levelAttributesBonus{ 5 };
				const double m_bonusDamageForMainAttributeMultiplier{ 0.5 };
				const int m_defaultDamage{ 10 };
				const int m_defaultHp{ 100 };
				const double m_bonusHPForStrengthMultiplier{ 0.5 };
				const int m_defaultStamina{ 30 };
				const int m_staminaPerLevelBonus{ 5 };
			};

			std::unique_ptr<Attributes> AttributesFactory::create(const weapons::Weapon* const weapon, int level, int strength, int agility, characters::CharacterType characterType)
			{
				int totalStrength = strength + (pImpl->m_levelAttributesBonus * level);
				int totalAgility = agility + (pImpl->m_levelAttributesBonus * level);
				int weaponDamage = (weapon == nullptr) ? 0 : weapon->getDamage();
				int totalDamage = weaponDamage + pImpl->m_defaultDamage + 
					(((characterType == characters::CharacterType::strong) ? strength : agility) * pImpl->m_bonusDamageForMainAttributeMultiplier);
				int hp = pImpl->m_defaultHp + (pImpl->m_bonusHPForStrengthMultiplier * totalStrength);
				int stamina = pImpl->m_defaultStamina + (pImpl->m_staminaPerLevelBonus * level);

				return std::make_unique<Attributes>(hp, level, totalDamage, totalStrength, totalAgility, stamina);
			}
		}
	}
}