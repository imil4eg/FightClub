#include <stdexcept>

#include "Equipment.h"

int Equipment::getArmorValue(HitDirection hitDirection) const
{
	const Armor* armor;
	switch (hitDirection)
	{
	case HitDirection::head:
		armor = this->m_head;
		break;
	case HitDirection::body:
		armor = this->m_body;
		break;
	case HitDirection::legs:
		armor = this->m_legs;
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