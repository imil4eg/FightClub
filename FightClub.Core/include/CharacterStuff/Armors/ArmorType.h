#pragma once

#include <string>

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

				std::string to_string(ArmorType type);
			}
		}
	}
}