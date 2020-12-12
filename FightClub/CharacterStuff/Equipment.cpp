#include <stdexcept>

#include "CharacterStuff/Equipment.h"

namespace fightclub
{
	namespace characterstuff
	{
		int Equipment::getArmorValue(battle::HitDirection hitDirection) const
		{
			const armors::Armor* armor;
			switch (hitDirection)
			{
			case battle::HitDirection::head:
				armor = this->m_head.get();
				break;
			case battle::HitDirection::body:
				armor = this->m_body.get();
				break;
			case battle::HitDirection::legs:
				armor = this->m_legs.get();
				break;
			default:
				throw std::out_of_range("Hit directory not implemented.");
			}

			if (armor == nullptr)
			{
				return 0;
			}
			else
			{
				return armor->getArmor();
			}
		}
	}
}