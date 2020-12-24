#pragma once

#include <string>

namespace fightclub
{
	namespace core
	{
		namespace battle
		{
			enum class HitDirection
			{
				head,
				body,
				legs,
				max_hit_direction
			};

			std::string operator+(std::string value, HitDirection hitDirection);
		}
	}
}