#pragma once

#include <numeric>

#include "Characters/Character.h"
#include "CharacterStuff/BodyPart.h"
#include "CharacterStuff/Abilities/Ability.h"
#include "CharacterStuff/Abilities/AbilityType.h"
#include "Battle/Fighters/Fighter.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			class DamageCalculator
			{
			public:
				static int Calculate(const characters::Character& character, const characters::Character& target,
					characterstuff::BodyPart hitDirection,
					characterstuff::BodyPart enemyProtectingPart,
					std::vector<fighters::Fighter::buffWithDuration_t>& characterBuffs,
					std::vector<fighters::Fighter::buffWithDuration_t>& enemyBuffs);

			private:
				static int calculateBuffs(std::vector<fighters::Fighter::buffWithDuration_t>& buffs, characterstuff::abilities::AbilityType type);
			};
		}
	}
}