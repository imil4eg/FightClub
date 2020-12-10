#pragma once

#include <memory>

#include "Characters/Character.h"
#include "CharacterStuff/Weapons/Weapon.h"
#include "CharacterStuff/Armors/Armor.h"

namespace fightclub 
{
	namespace models 
	{
		struct UserDataModel
		{
			std::unique_ptr<Character> character;
			std::vector<std::unique_ptr<Armor>> armors;
			std::vector<std::unique_ptr<Weapon>> weapons;

			UserDataModel() = default;

			UserDataModel(UserDataModel&& udm) noexcept : 
				character{std::move(udm.character)},
				armors{ std::move(udm.armors) },
				weapons{ std::move(udm.weapons) }
			{
			}
		};
	}
}