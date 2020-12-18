#include <string>

#include "Battle/HitDirection.h"

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			std::string operator+ (std::string value, HitDirection hitDirection)
			{
				std::string hitDirectionStr;
				switch (hitDirection)
				{
				case fightclub::core::battle::HitDirection::head:
					hitDirectionStr = "head";
					break;
				case fightclub::core::battle::HitDirection::body:
					hitDirectionStr = "body";
					break;
				case fightclub::core::battle::HitDirection::legs:
					hitDirectionStr = "legs";
					break;
				default:
					throw std::exception("Specified hit direction not found.");
				}

				return value + hitDirectionStr;
			}
		}
	}
}