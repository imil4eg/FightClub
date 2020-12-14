#include "CharacterStuff/Weapons/Weapon.h"

namespace fightclub
{
	namespace characterstuff
	{
		namespace weapons
		{
			std::ostream& operator<<(std::ostream& out, const Weapon& weapon)
			{
				out << "Name: " << weapon.m_name << " damage: " << weapon.m_damage;

				return out;
			}
		}
	}
}