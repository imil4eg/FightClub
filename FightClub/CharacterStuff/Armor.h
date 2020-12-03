#ifndef ARMOR_H
#define ARMOR_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "Attributes.h"

class Armor
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
	const boost::uuids::uuid m_id;
	Attributes m_attributes;
	Type m_type{};
	int m_armor{};

public:
	Armor(Attributes attributes, Type type, int armor) :
		m_id{boost::uuids::random_generator()()},
		m_attributes{ attributes },
		m_type {type},
		m_armor{armor}
	{
	}

	const boost::uuids::uuid getId() const { return m_id; }
	Attributes& getAttributes() { return m_attributes; }
	Type getType() const { return m_type; }
	int getArmor() const { return m_armor; }
};

#endif // !ARMOR_H

