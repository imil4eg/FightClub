#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>
#include <fstream>

#include "Common/RandomGenerator.h"
#include "CharacterStuff/Weapons/WeaponStorage.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

std::unique_ptr<Weapon> WeaponStorage::getRandomWeapon() const
{
	std::ifstream input{ m_config->get(ConfigKeys::weaponsFile) };

	if (!input.good())
		return nullptr;

	json weaponsJson;
	input >> weaponsJson;

	std::vector<Weapon> weapons{};
	for (auto& weapon : weaponsJson[m_weaponsKey].items())
	{
		auto id{ boost::lexical_cast<boost::uuids::uuid>(weapon.value()[m_idKey].get<std::string>()) };
		auto name{ weapon.value()[m_nameKey].get<std::string>() };
		int damage{ weapon.value()[m_damageKey].get<int>() };

		weapons.push_back(Weapon{id, name, damage});
	}

	auto randomWeaponId{ RandomGenerator::getBetween(0, static_cast<int>(weapons.size()) - 1) };

	return std::make_unique<Weapon>(weapons[randomWeaponId]);
}

std::unique_ptr<Weapon> WeaponStorage::getWeaponOrDefault(const boost::uuids::uuid& id) const
{
	std::ifstream input{ m_config->get(ConfigKeys::weaponsFile) };

	if (!input.good())
		return nullptr;

	json weaponsJson;
	input >> weaponsJson;

	auto idStr{ boost::lexical_cast<std::string>(id) };
	for (auto& weapon : weaponsJson[m_weaponsKey].items())
	{
		if (idStr != weapon.value()[m_idKey].get<std::string>())
		{
			continue;
		}

		auto id{ boost::lexical_cast<boost::uuids::uuid>(weapon.value()[m_idKey].get<std::string>()) };
		auto name{ weapon.value()[m_nameKey].get<std::string>() };
		int damage{ weapon.value()[m_damageKey].get<int>() };

		return std::make_unique<Weapon>(id, name, damage);
	}

	return nullptr;
}