#include "CharacterStuff/AttributeConsts.h"
#include "CharacterStuff/AttributesFactory.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			std::unique_ptr<Attributes> AttributesFactory::create(const weapons::Weapon* const weapon, int level, int strength, int agility,
				characters::CharacterType characterType) 
			{
				int totalStrength = strength + (AttributeConsts::AttributesPerLevelMultiplier * level);
				int totalAgility = agility + (AttributeConsts::AttributesPerLevelMultiplier * level);
				int weaponDamage = (weapon == nullptr) ? 0 : weapon->getDamage();
				int totalDamage = weaponDamage + AttributeConsts::DefaultDamage + 
					(((characterType == characters::CharacterType::strong) ? strength : agility) * AttributeConsts::BonusDamageForMainAttributeMultiplier);
				int hp = AttributeConsts::DefaultHp + (AttributeConsts::BonusHPForStrengthMultiplier * totalStrength);
				int stamina = AttributeConsts::DefaultStamina + (AttributeConsts::StaminaPerLevelBonus * level);

				return std::make_unique<Attributes>(hp, level, totalDamage, totalStrength, totalAgility, stamina);
			}

			std::unique_ptr<Attributes> AttributesFactory::create(const characters::Character& character, int strength, int agility)
			{
				return create(character.getWeapon(), character.getAttributes()->getLevel(), strength, agility, character.getCharcterType());
			}
		}
	}
}