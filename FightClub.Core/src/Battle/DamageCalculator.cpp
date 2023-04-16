#include "Battle/DamageCalculator.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			int DamageCalculator::Calculate(const characters::Character& character, const characters::Character& target,
				characterstuff::BodyPart hitDirection,
				characterstuff::BodyPart enemyProtectingPart,
				std::vector<fighters::Fighter::buffWithDuration_t>& characterBuffs,
				std::vector<fighters::Fighter::buffWithDuration_t>& enemyBuffs)
			{
				int characterDamageBuff{ calculateBuffs(characterBuffs, characterstuff::abilities::AbilityType::damage_boost) };
				int targetArmorBuff{ calculateBuffs(enemyBuffs, characterstuff::abilities::AbilityType::armor_boost) };

				int totalDamage{ (character.getAttributes()->getDamage() + characterDamageBuff) - 
					 (target.getEquipment().getArmorValue(hitDirection) + targetArmorBuff) };

				// If enemy correctly predicted hit direction then reduce 20% from damage.
				if (hitDirection == enemyProtectingPart)
				{
					int twentyPercentFromDamage{ (totalDamage * 20) / 100 };
					totalDamage -= twentyPercentFromDamage;
				}

				return totalDamage;
			}

			int DamageCalculator::calculateBuffs(std::vector<fighters::Fighter::buffWithDuration_t>& buffs, characterstuff::abilities::AbilityType type)
			{
				int sum{};
				for (auto it{ buffs.begin() }; it != buffs.end(); ++it)
				{
					sum += it->first->getType() == type ? it->first->getValue() : 0;
				}

				return sum;
			}
		}
	}
}