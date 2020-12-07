#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Armors/Armor.h"
#include "../Battle/HitDirection.h"

class Equipment
{
private:
	const Armor* m_head;
	const Armor* m_body;
	const Armor* m_legs;

private:
	Equipment(const Armor* head = nullptr, const Armor* body = nullptr, const Armor* legs = nullptr) : 
		m_head{head},
		m_body{body},
		m_legs{ legs }
	{
	}

public:
	~Equipment()
	{
		delete m_head;
		delete m_body;
		delete m_legs;

		m_head = nullptr;
		m_body = nullptr;
		m_legs = nullptr;
	}
	
	friend class BotFactory;
	friend class JsonGameDataProcesser;
	friend class CharacterFactory;

	const Armor* getHelment() const { return m_head; }
	const Armor* getCuirasse() const { return m_body; }
	const Armor* getBoots() const { return m_legs; }
	int getArmorValue(HitDirection hitDirection) const;
};

#endif // !EQUIPMENT_H

