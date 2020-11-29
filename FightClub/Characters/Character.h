#ifndef CHARACTER_H
#define CHARACTER_H

#include "../CharacterStuff/Attributes.h"
#include "../CharacterStuff/Armor.h"
#include "../CharacterStuff/Equipment.h"
#include "../Battle/HitDirection.h"
#include "../CharacterStuff/Weapon.h"

class Character
{
private:
	Attributes* m_attributes;
	Equipment* m_equipment;
	Weapon* m_weapon;

public:
	Character(Attributes* const attributes, Equipment* const equipment, Weapon* const weapon = nullptr) : 
		m_attributes {attributes},
		m_equipment{equipment},
		m_weapon{weapon}
	{
		attributes->setDamageFromWeapon(weapon);
	}

	virtual ~Character()
	{
		delete m_attributes;
		delete m_equipment;
		delete m_weapon;
	};

	Attributes* getAttributes() { return m_attributes; }
	Equipment* getEquipment(){ return m_equipment; }
	Weapon* getWeapon() { return m_weapon; }

	void restoreHp() { m_attributes->setHp(100); }
	void hit(Character& enemy, int damage)
	{
		enemy.getAttributes()->setHp(enemy.getAttributes()->getHp() - damage);
	}
	virtual void hit(Character& enemy, HitDirection hitDirection) = 0;
	virtual void playTurn(Character& target) = 0;
};

#endif // !CHARACTER_H

