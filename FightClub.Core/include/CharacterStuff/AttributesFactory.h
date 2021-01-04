#pragma once

#include "IAttributesFactory.h"
#include "Characters/Character.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			class AttributesFactory : public IAttributesFactory
			{
			public:
				AttributesFactory() = default;
				~AttributesFactory() = default;

				std::unique_ptr<Attributes> create(const weapons::Weapon* const weapon, int level, int stength, int agility, characters::CharacterType characterType) override;
				std::unique_ptr<Attributes> create(const characters::Character& character, int strength, int agility) override;
			};
		}
	}
}