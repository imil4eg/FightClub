#pragma once

#include <memory>

#include "Attributes.h"
#include "Characters/CharacterType.h"
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
			};
		}
	}
}