#ifndef ARMOR_H
#define ARMOR_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "../Attributes.h"

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
	const std::string m_name;
	Attributes* m_attributes;
	Type m_type{};
	int m_armor{};

protected:
	Armor(const std::string& name, Type type, int armor, Attributes* attributes = nullptr) :
		m_id{boost::uuids::random_generator()()},
		m_name{name},
		m_attributes{ attributes },
		m_type {type},
		m_armor{armor}
	{
	}

public:
	Armor(const Armor* armor) : 
		m_id{armor->m_id},
		m_name{armor->m_name},
		m_attributes{armor->m_attributes},
		m_type{ armor->m_type },
		m_armor{ armor->m_armor }
	{
	}

	virtual ~Armor()
	{
		delete m_attributes;
	}

	const boost::uuids::uuid getId() const { return m_id; }
	const std::string& getName() const { return m_name; }
	const Attributes* getAttributes() { return m_attributes; }
	Type getType() const { return m_type; }
	int getArmor() const { return m_armor; }
};

#endif // !ARMOR_H

