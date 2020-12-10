#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "Weapons/Weapon.h"

class Attributes
{
private:
	int m_hp{};
	int m_damage{};
	int m_level{};
	int m_stength{};
	int m_agility{};
	int m_stamina{};

public:
	Attributes(int hp, int level, int damage, int strength, int agility, int stamina) :
		m_hp{ hp },
		m_level{ level },
		m_damage{ damage },
		m_stength{ strength },
		m_agility{ agility },
		m_stamina{ stamina }
	{
	}
	
	int getHp() const { return m_hp; }
	void setHp(int hp) { m_hp = hp; }
	int getDamage() const { return m_damage; }
	int getLevel() const { return m_level; }
	int getStrength() const { return m_stength; }
	int getAgility() const { return m_agility; }
	int getStamina() const { return m_stamina; }
};


#endif // !ATTRIBUTES_H

