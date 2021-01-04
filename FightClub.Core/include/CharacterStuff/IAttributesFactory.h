#pragma once

#include <memory>

#include "Attributes.h"
#include "Characters/CharacterType.h"
#include "Characters/Character.h"
#include "Weapons/Weapon.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			class IAttributesFactory
			{
			public:
				virtual ~IAttributesFactory() noexcept = default;
				virtual std::unique_ptr<Attributes> create(const weapons::Weapon* const weapon, int level, int stength, int agility, characters::CharacterType characterType) = 0;
				virtual std::unique_ptr<Attributes> create(const characters::Character& character, int strength, int agility) = 0;
			};
		}
	}
}