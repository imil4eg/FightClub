#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Attributes.h"

class Equipment
{
public:
	enum class Type
	{
		head,
		body,
		hands,
		legs,
		max_equipment_types
	};

private:
	Attributes m_attributes;
	Type m_type{};
	int m_armor{};

public:
	Equipment(Attributes attributes, Type type, int armor) :
		m_attributes{ attributes }, 
		m_type{type},
		m_armor{ armor }
	{
	}

	Attributes& getAttributes() { return m_attributes; }
	Type getType() { return m_type; }
	int getArmor() const { return m_armor; }
};

#endif // !EQUIPMENT_H

