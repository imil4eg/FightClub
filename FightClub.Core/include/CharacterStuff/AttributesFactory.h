#pragma once

#include "IAttributesFactory.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			class AttributesFactory : public IAttributesFactory
			{
			private:
				class Impl;
				std::unique_ptr<Impl> pImpl;

			public:
				std::unique_ptr<Attributes> create(const weapons::Weapon* const weapon, int level, int stength, int agility, characters::CharacterType characterType) override;
			};
		}
	}
}