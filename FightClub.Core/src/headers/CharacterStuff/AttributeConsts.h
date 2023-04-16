#pragma once

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			class AttributeConsts
			{
			public:
				static constexpr int	 AttributesPerLevelMultiplier{ 2 };
				static constexpr int	 UserCharacterUpgradeAttributePerLevel{ 2 };
				static constexpr double  BonusDamageForMainAttributeMultiplier{ 0.5 };
				static constexpr int	 DefaultDamage{ 10 };
				static constexpr int	 DefaultHp{ 100 };
				static constexpr double  BonusHPForStrengthMultiplier{ 0.5 };
				static constexpr int	 DefaultStamina{ 30 };
				static constexpr int	 StaminaPerLevelBonus{ 5 };

				AttributeConsts() = delete;
			};
		}
	}
}