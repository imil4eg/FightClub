#include "CharacterStuff/Armors/ArmorType.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace armors
			{
				std::string to_string(ArmorType type)
				{
					switch (type)
					{
					case core::characterstuff::armors::ArmorType::head:
						return "helmet";
					case core::characterstuff::armors::ArmorType::body:
						return "cuirasse";
					case core::characterstuff::armors::ArmorType::hands:
						return "gloves";
					case core::characterstuff::armors::ArmorType::legs:
						return "boots";
					default:
						throw std::exception("Not implemented armor type.");
					}
				}
			}
		}
	}
}