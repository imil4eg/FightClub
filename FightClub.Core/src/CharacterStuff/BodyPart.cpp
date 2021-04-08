#include <string>
#include <stdexcept>

#include "CharacterStuff/BodyPart.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			std::string operator+ (std::string value, BodyPart hitDirection)
			{
				std::string hitDirectionStr;
				switch (hitDirection)
				{
				case characterstuff::BodyPart::head:
					hitDirectionStr = "head";
					break;
				case characterstuff::BodyPart::body:
					hitDirectionStr = "body";
					break;
				case characterstuff::BodyPart::legs:
					hitDirectionStr = "legs";
					break;
				default:
					throw std::runtime_error("Specified hit direction not found.");
				}

				return value + hitDirectionStr;
			}
		}
	}
}