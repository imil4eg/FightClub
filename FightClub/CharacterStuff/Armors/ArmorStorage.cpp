#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <fstream>
#include <exception>

#include "CharacterStuff/Armors/ArmorStorage.h"
#include "Common/RandomGenerator.h"
#include "IO/JsonAttributes.h"

#include "../../libs/nlohmann/json.hpp"

using json = nlohmann::json;

std::unique_ptr<Armor> ArmorStorage::getOrDefault(const boost::uuids::uuid& id)
{
	std::ifstream armorsFile{ m_confilg->get(ConfigKeys::armorsFile) };

	if (!armorsFile.good())
		return nullptr;

	json armorsJson;
	armorsFile >> armorsJson;

	auto idStr{ boost::lexical_cast<std::string>(id) };
	for (auto& armor : armorsJson[fightclub::io::JsonAttributes::Armors].items())
	{
		if (idStr != armor.value()[fightclub::io::JsonAttributes::Id].get<std::string>())
		{
			continue;
		}

		auto id{ boost::lexical_cast<boost::uuids::uuid>(armor.value()[fightclub::io::JsonAttributes::Id].get<std::string>()) };
		auto name{ armor.value()[fightclub::io::JsonAttributes::Name].get<std::string>() };
		auto type{ static_cast<fightclub::characterstuff::armors::ArmorType>(armor.value()[fightclub::io::JsonAttributes::Type].get<int>()) };
		auto armorValue{ armor.value()[fightclub::io::JsonAttributes::Value].get<int>() };

		return std::make_unique<Armor>(id, name, type, armorValue);
	}

	return nullptr;
}

std::unique_ptr<Armor> ArmorStorage::getRandom(fightclub::characterstuff::armors::ArmorType armorType)
{
	std::ifstream armorsFile{ m_confilg->get(ConfigKeys::armorsFile) };

	if (!armorsFile.good())
		return nullptr;

	json armorsJson;

	auto armorTypeInt{ static_cast<int>(armorType) };
	std::vector<Armor> armors{};
	for (auto& armor : armorsJson[fightclub::io::JsonAttributes::Armors].items())
	{
		if (armorTypeInt != armor.value()[fightclub::io::JsonAttributes::Type].get<int>())
		{
			continue;
		}

		auto id{ boost::lexical_cast<boost::uuids::uuid>(armor.value()[fightclub::io::JsonAttributes::Id].get<std::string>()) };
		auto name{ armor.value()[fightclub::io::JsonAttributes::Name].get<std::string>() };
		auto type{ static_cast<fightclub::characterstuff::armors::ArmorType>(armor.value()[fightclub::io::JsonAttributes::Type].get<int>()) };
		auto armorValue{ armor.value()[fightclub::io::JsonAttributes::Value].get<int>() };

		Armor armor{ id, name, type, armorValue };
		armors.push_back(armor);
	}

	auto randomArmorId{ RandomGenerator::getBetween(0, armors.size()) };

	if (randomArmorId == armors.size())
	{
		return nullptr;
	}

	return std::make_unique<Armor>(std::move(armors[randomArmorId]));

	return nullptr;
}