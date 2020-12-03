#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

class Weapon
{
private:
	boost::uuids::uuid m_id{};
	std::string m_name{};
	int m_damage{};

public:
	Weapon(std::string name, int damage) : 
		m_id {boost::uuids::random_generator()()},
		m_name{name},
		m_damage{ damage }
	{
	}

	Weapon(Weapon&& weapon) noexcept : 
		m_id{weapon.m_id},
		m_name{ weapon.m_name },
		m_damage{ weapon.m_damage }
	{
		weapon.m_id = boost::uuids::nil_uuid();
		weapon.m_name = nullptr;
		weapon.m_damage = 0;
	}

	virtual ~Weapon() noexcept = default;
	int getDamage() const { return m_damage; }
	const std::string& getName() const { return m_name; }
	boost::uuids::uuid& getId() { return m_id; }
};

#endif // !WEAPON_H

