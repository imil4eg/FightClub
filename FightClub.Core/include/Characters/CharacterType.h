#pragma once

#include <string>
#include <iostream>

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			enum class CharacterType
			{
				strong,
				smooth,
				max_character_type
			};

			std::ostream& operator<<(std::ostream& out, CharacterType characterType);
		}
	}
}