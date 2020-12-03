#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Armor.h"
#include "../Battle/HitDirection.h"

class Equipment
{
private:
	Armor* m_head;
	Armor* m_body;
	Armor* m_legs;

public:
	Equipment(Armor* const head = nullptr, Armor* const body = nullptr, Armor* const legs = nullptr) : 
		m_head{head},
		m_body{body},
		m_legs{ legs }
	{
	}


	const Armor* getHelment() const { return m_head; }
	const Armor* getCuirasse() const { return m_body; }
	const Armor* getBoots() const { return m_legs; }
	int getArmorValue(HitDirection hitDirection) const;
};

#endif // !EQUIPMENT_H

