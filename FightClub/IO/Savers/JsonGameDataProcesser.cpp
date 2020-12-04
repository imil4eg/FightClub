#include <iomanip>
#include <fstream>

#include "JsonGameDataProcesser.h"

#include "../../libs/nlohmann/json.hpp"

using json = nlohmann::json;

void addEquipmentAttribute(json& j, std::string attributeName, const Armor* armor)
{
	j["equipment"][attributeName] = armor == nullptr ? boost::uuids::nil_uuid() : armor->getId();
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

Character* GameDataProcesser::load()
{
	std::ifstream input{ "file.json" };
	json characterJson;
	input >> characterJson;


}
