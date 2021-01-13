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
					boost,
					attack,
					trap,
					max_type
				};

				std::string to_string(AbilityType type);
			}
		}
	}
}