#include "CharacterStuff/Armors/Armor.h"

namespace fightclub
{
	namespace characterstuff
	{
		namespace armors
		{
			std::ostream& operator<<(std::ostream& out, const Armor& armor)
			{
				out << armor.m_name << " defence: " << armor.m_armor;

				return out;
			}
		}
	}
}