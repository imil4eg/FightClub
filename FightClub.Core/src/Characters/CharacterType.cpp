#include "Characters/CharacterType.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			std::ostream& operator<<(std::ostream& out, CharacterType characterType)
			{
				switch (characterType)
				{
				case fightclub::core::characters::CharacterType::strong:
					out << "strong";
					break;
				case fightclub::core::characters::CharacterType::smooth:
					out << "smooth";
					break;
				default:
					throw std::runtime_error("Not existing character type specified.");
				}

				return out;
			}
		}
	}
}