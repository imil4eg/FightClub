#pragma once

#include <string>

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			enum class BodyPart
			{
				head,
				body,
				legs,
				max_body_part
			};

			std::string operator+(std::string value, BodyPart hitDirection);
		}
	}
}