#include "CharacterStuff/Armors/ArmorType.h"

namespace fightclub
{
	namespace characterstuff
	{
		namespace armors
		{
			std::ostream& operator<<(std::ostream& out, ArmorType type)
			{
				std::string armorTypeStr{};
				switch (type)
				{
				case ArmorType::head:
					armorTypeStr = "helmet";
					break;
				case ArmorType::body:
					armorTypeStr = "cuirasse";
					break;
				case ArmorType::hands:
					armorTypeStr = "gloves";
					break;
				case ArmorType::legs:
					armorTypeStr = "boots";
				default:
					throw std::exception("Not implemented armor type.");
				}

				out << armorTypeStr;

				return out;
			}
		}
	}
}