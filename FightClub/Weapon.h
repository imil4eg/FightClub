#ifndef WEAPON_H
#define WEAPON_H

class Weapon
{
private:
	int m_damage{};

public:
	Weapon(int damage) : m_damage{ damage }
	{
	}

	int getDamage() const { return m_damage; }
};

#endif // !WEAPON_H

