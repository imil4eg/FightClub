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
				armor = this->getHelmet();
				break;
			case battle::HitDirection::body:
				armor = this->getCuirasse();
				break;
			case battle::HitDirection::legs:
				armor = this->getBoots();
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

		int Equipment::getTotalArmor() const
		{
			return getArmorValue(this->getHelmet()) + getArmorValue(this->getCuirasse()) + getArmorValue(this->getBoots());
		}

		int Equipment::getArmorValue(const armors::Armor* armor) const
		{
			return armor == nullptr ? 0 : armor->getArmor();
		}
	}
}