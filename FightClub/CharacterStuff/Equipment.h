#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <memory>

#include "Armors/Armor.h"
#include "../Battle/HitDirection.h"

class Equipment
{
private:
	std::unique_ptr<Armor> m_head;
	std::unique_ptr<Armor> m_body;
	std::unique_ptr<Armor> m_legs;

public:
	Equipment(std::unique_ptr<Armor> head = {}, std::unique_ptr<Armor> body = {}, std::unique_ptr<Armor> legs = {}) :
		m_head{ std::move(head) },
		m_body{ std::move(body) },
		m_legs{ std::move(legs) }
	{
	}

	const Armor* getHelment() const { return m_head.get(); }
	const Armor* getCuirasse() const { return m_body.get(); }
	const Armor* getBoots() const { return m_legs.get(); }
	int getArmorValue(HitDirection hitDirection) const;
};

#endif // !EQUIPMENT_H

