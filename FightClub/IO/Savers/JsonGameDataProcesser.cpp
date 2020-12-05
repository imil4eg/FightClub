#include <iomanip>
#include <fstream>

#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#include "../../Characters/Player.h"
#include "JsonGameDataProcesser.h"

void addEquipmentAttribute(json& j, std::string attributeName, const Armor* armor)
{
	j["equipment"][attributeName] = armor == nullptr ? boost::uuids::nil_uuid() : armor->getId();
}

const Armor* JsonGameDataProcesser::getArmor(json& j, const std::string& attributename)
{
	auto id{ j["equipment"][attributename].get <std::string>() };

	return m_armorStorage->getOrDefault(boost::lexical_cast<boost::uuids::uuid>(id));
}

void JsonGameDataProcesser::save(Character& character) const
{
	json j;

	j["attributes"] = nullptr;
	j["attributes"]["strength"] = character.getAttributes()->getStrength();
	j["attributes"]["agility"] = character.getAttributes()->getAgility();
	j["attributes"]["level"] = character.getAttributes()->getLevel();

	j["equipment"] = nullptr;
	addEquipmentAttribute(j, "head", character.getEquipment()->getHelment());
	addEquipmentAttribute(j, "cuirasse", character.getEquipment()->getCuirasse());
	addEquipmentAttribute(j, "boots", character.getEquipment()->getBoots());

	j["weapon"] = character.getWeapon() == nullptr ? boost::uuids::nil_uuid() : character.getWeapon()->getId();
	j["characterType"] = character.getCharcterType();

	std::ofstream outFile{ "file.json" };
	outFile << std::setw(4) << j << std::endl;
}

Character* JsonGameDataProcesser::load()
{
	std::ifstream input{ "file.json" };
	json characterJson;
	input >> characterJson;

	int strength = characterJson["attributes"]["strength"].get<int>();
	int agility = characterJson["attributes"]["agility"].get<int>();
	int level = characterJson["attributes"]["level"].get<int>();
	auto characterType = static_cast<CharacterType>(characterJson["characterType"].get<int>());

	auto weaponId{ boost::lexical_cast<boost::uuids::uuid>(characterJson["weapon"].get<std::string>()) };
	auto weapon{ m_weaponStorage->getWeaponOrDefault(weaponId) };

	auto attributes{ m_attributesFactory->create(weapon, level, strength, agility, characterType) };

	auto head{ getArmor(characterJson, m_headAttribute) };
	auto cuirass{ getArmor(characterJson, m_cuirasseAttribute) };
	auto legs{ getArmor(characterJson, m_legsAttribute) };

	auto equipment{ new Equipment{head, cuirass, legs} };

	return new Player{ &attributes, equipment, characterType, weapon };
}
