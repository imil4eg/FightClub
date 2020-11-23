#ifndef CHARACTER_H
#define CHARACTER_H

#include "Attributes.h"
#include "Equipment.h"
#include "Weapon.h"

class Character
{
private:
	Attributes m_attributes;
	Equipment m_equipment;
	Weapon m_weapon;

public:
	Character(const Attributes& attributes, const Equipment& equipment, const Weapon& weapon) : 
		m_attributes {attributes},
		m_equipment{equipment},
		m_weapon{weapon}
	{
	}

	Attributes& getAttributes() { return m_attributes; }
	Equipment& getEquipment() { return m_equipment; }
	Weapon& getWeapon() { return m_weapon; }
};

#endif // !CHARACTER_H

