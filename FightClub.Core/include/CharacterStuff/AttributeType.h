#pragma once

#include <string>
#include <iostream>

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			enum class AttributeType
			{
				strong,
				smooth,
				max_attribute_type
			};

			std::ostream& operator<<(std::ostream& out, AttributeType attributeType);
			std::string to_string(AttributeType attributeType);
		}
	}
}