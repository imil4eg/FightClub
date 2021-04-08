#include "CharacterStuff/Armors/ArmorType.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace armors
			{
				std::ostream& operator<<(std::ostream& out, ArmorType type)
				{
					std::string result;
					switch (type)
					{
					case core::characterstuff::armors::ArmorType::head:
						result = "helmet";
						break;
					case core::characterstuff::armors::ArmorType::body:
						result = "cuirasse";
						break;
					case core::characterstuff::armors::ArmorType::hands:
						result = "gloves";
						break;
					case core::characterstuff::armors::ArmorType::legs:
						result = "boots";
						break;
					default:
						throw std::runtime_error("Not implemented armor type.");
					}

					out << result;

					return out;
				}
			}
		}
	}
}