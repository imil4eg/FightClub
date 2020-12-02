#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>

#include "../Common/RandomGenerator.h"
#include "WeaponStorage.h"

const Weapon& WeaponStorage::getWeapon(const boost::uuids::uuid& id) const
{
	if (m_weapons.find(id) == m_weapons.end())
	{
		throw std::exception("Weapon with specified id not found.");
	}

	return m_weapons.at(id);
}

const Weapon& WeaponStorage::getRandomWeapon() const
{
	auto randomWeaponId{ RandomGenerator::getBetween(0, m_weaponIds.size() - 1) };

	return m_weapons.at(m_weaponIds[randomWeaponId]);
}