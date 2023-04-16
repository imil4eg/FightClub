#pragma once

#include "AbilitiesContainer.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace abilities
			{
				class IAbilitiesDisplayer
				{
				public:
					virtual ~IAbilitiesDisplayer() = default;

					virtual void showAll(const AbilitiesContainer& container) const = 0;
					virtual void showSelected(const AbilitiesContainer& container) const = 0;
					virtual void show(const Ability& ability) const = 0;
				};
			}
		}
	}
}