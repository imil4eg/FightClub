#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Armor.h"

class Equipment
{
private:
	Armor m_head;
	Armor m_body;
	Armor m_legs;
	Armor m_hands;

public:
	Armor(const Armor& head, const Amor& body, const Armor& legs, const Armor& hands) : 
		m_head{head},
		m_body{body},
		m_legs{ legs },
		m_hands{ m_hands }
	{
	}

	const Armor& getHead() const { return m_head; }
	const Armor& getBody() const { return m_body; }
	const Armor& getLegs() const { return m_legs; }
	const Armor& getHands() const { return m_hands; }
};

#endif // !EQUIPMENT_H

