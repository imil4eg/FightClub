#ifndef ATTRIBUTES_FACTORY_H
#define ATTRIBUTES_FACTORY_H

#include "IAttributesFactory.h"

namespace fightclub
{
	namespace characterstuff
	{
		class AttributesFactory : public IAttributesFactory
		{
		private:
			const int m_levelAttributesBonus{ 5 };
			const double m_bonusDamageForMainAttributeMultiplier{ 0.5 };
			const int m_defaultDamage{ 10 };
			const int m_defaultHp{ 100 };
			const double m_bonusHPForStrengthMultiplier{ 0.5 };
			const int m_defaultStamina{ 30 };
			const int m_staminaPerLevelBonus{ 5 };

		public:
			std::unique_ptr<Attributes> create(const weapons::Weapon* const weapon, int level, int stength, int agility, characters::CharacterType characterType) override;
		};
	}
}

#endif // !ATTRIBUTES_FACTORY_H

