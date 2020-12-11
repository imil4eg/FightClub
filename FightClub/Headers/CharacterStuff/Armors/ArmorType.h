#pragma once

#include <iostream>

namespace fightclub
{
	namespace characterstuff
	{
		namespace armors
		{
			enum class ArmorType
			{
				head,
				body,
				hands,
				legs,
				max_equipment_types
			};

			std::ostream& operator<<(std::ostream& out, ArmorType type);
		}
	}
}