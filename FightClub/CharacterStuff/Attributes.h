#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "Weapon.h"

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
	Attributes(int hp, int level, int strength, int agility) : 
		m_hp{hp},
		m_level{level},
		m_stength{ strength },
		m_agility{ agility }
	{
	}

	int getHp() const { return m_hp; }
	void setHp(int hp) { m_hp = hp; }
	int getDamage() const { return m_damage; }
	int getLevel() const { return m_level; }
	int getStrength() const { return m_stength; }
	int getAgility() const { return m_agility; }
	int getStamina() const { return m_stamina; }

	void setDamageFromWeapon(const Weapon* weapon)
	{
		if (weapon != nullptr)
			m_damage += weapon->getDamage();
	}
};


#endif // !ATTRIBUTES_H

