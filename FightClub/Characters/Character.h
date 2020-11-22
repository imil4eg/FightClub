#ifndef CHARACTER_H
#define CHARACTER_H

#include "Attributes.h"
#include "Equipment.h"
#include "Weapon.h"

class Character
{
private:
	Attributes m_attributes;
	Equipment m_head;
	Equipment m_body;
	Equipment m_legs;
	Equipment m_hands;
	Weapon m_weapon;

public:
	Character(Attributes attributes) : 
		m_attributes {attributes}
	{
	}

	Attributes& getAttributes() { return m_attributes; }
};

#endif // !CHARACTER_H

