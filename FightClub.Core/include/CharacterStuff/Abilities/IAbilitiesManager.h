#pragma once

#include <vector>

#include "Characters/Character.h"
#include "CharacterStuff/Abilities/Ability.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace abilities
			{
				class IAbilitiesManager
				{
				public:
					virtual ~IAbilitiesManager() = default;

					virtual void enter(characters::Character& character) = 0;
					virtual void changeSelectedAbilities(AbilitiesContainer& container) const = 0;
				};
			}
		}
	}
}