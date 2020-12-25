#pragma once

#include <string>
#include <iostream>

namespace fightclub
{
	namespace core
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
}