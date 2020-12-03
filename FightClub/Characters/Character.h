#ifndef CHARACTER_H
#define CHARACTER_H

#include "../CharacterStuff/Attributes.h"
#include "../CharacterStuff/Armor.h"
#include "CharacterType.h"
#include "../CharacterStuff/Equipment.h"
#include "../Battle/HitDirection.h"
#include "../CharacterStuff/Weapon.h"

class Character
{
private:
	Attributes* m_attributes;
	Equipment* m_equipment;
	Weapon* m_weapon;
	CharacterType m_characterType;

public:
	Character(Attributes* attributes, Equipment* equipment, CharacterType characterType, Weapon* weapon = nullptr) :
		m_attributes {attributes},
		m_equipment{equipment},
		m_weapon{weapon},
		m_characterType{characterType}
	{
	}

	Character(Character&& character) noexcept : 
		m_attributes{character.m_attributes},
		m_equipment{character.m_equipment},
		m_weapon{ character.m_weapon },
		m_characterType{ character.m_characterType }
	{
		character.m_attributes = nullptr;
		character.m_equipment = nullptr;
		character.m_weapon = nullptr;
	}

	virtual ~Character()
	{
		delete m_attributes;
		delete m_equipment;
		delete m_weapon;
	};

	Attributes* getAttributes() const { return m_attributes; }
	Equipment* getEquipment() const{ return m_equipment; }
	Weapon* const getWeapon() { return m_weapon; }
	CharacterType getCharcterType() const { return m_characterType; }

	void restoreHp() { m_attributes->setHp(100); }
	void hit(Character& enemy, int damage)
	{
		enemy.getAttributes()->setHp(enemy.getAttributes()->getHp() - damage);
	}
	virtual void hit(Character& enemy, HitDirection hitDirection) = 0;
	virtual void playTurn(Character& target) = 0;
};

#endif // !CHARACTER_H

