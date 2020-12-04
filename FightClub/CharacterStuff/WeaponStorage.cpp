#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>

#include "../Common/RandomGenerator.h"
#include "WeaponStorage.h"

Weapon* WeaponStorage::getRandomWeapon() const
{
	auto randomWeaponId{ RandomGenerator::getBetween(0, static_cast<int>(m_weaponIds.size()) - 1) };

	return m_weapons.at(m_weaponIds[randomWeaponId]);
}

const Weapon* WeaponStorage::getWeaponOrDefault(const boost::uuids::uuid& id) const
{
	if (m_weapons.find(id) == m_weapons.end())
	{
		return nullptr;
	}

	return m_weapons.at(id);
}