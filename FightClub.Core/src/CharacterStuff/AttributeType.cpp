#include "CharacterStuff/AttributeType.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			std::ostream& operator<<(std::ostream& out, AttributeType attributeType)
			{
				out << to_string(attributeType);

				return out;
			}

			std::string to_string(AttributeType attributeType)
			{
				switch (attributeType)
				{
				case AttributeType::strong:
					return "Strength";
				case AttributeType::smooth:
					return "Agility";
				default:
					return "";
				}
			}
		}
	}
}