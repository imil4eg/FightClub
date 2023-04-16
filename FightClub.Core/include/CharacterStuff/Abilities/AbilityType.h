#pragma once

#include <string>

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace abilities
			{
				enum class AbilityType
				{
					damage_boost,
					armor_boost,
					trap,
					max_type
				};

				std::string to_string(AbilityType type);
			}
		}
	}
}