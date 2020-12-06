#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <iomanip>
#include <fstream>

#include "../../Characters/Player.h"
#include "../../Common/ConfigKeys.h"
#include "JsonGameDataProcesser.h"

void addEquipmentAttribute(json& j, std::string attributeName, const Armor* armor)
{
	j["equipment"][attributeName] = armor == nullptr ? boost::uuids::nil_uuid() : armor->getId();
}

const Armor* JsonGameDataProcesser::getArmor(json& j, const std::string& attributename)
{
	auto id{ j[m_equipmentAttribute][attributename].get <std::string>() };

	return m_armorStorage->getOrDefault(boost::lexical_cast<boost::uuids::uuid>(id));
}

void JsonGameDataProcesser::save(Character& character) const
{
	json j;

	j[m_attributesAttribute] = nullptr;
	j[m_attributesAttribute][m_strengthAttribute] = character.getAttributes()->getStrength();
	j[m_attributesAttribute][m_agilityAttribute] = character.getAttributes()->getAgility();
	j[m_attributesAttribute][m_levelAttribute] = character.getAttributes()->getLevel();

	j[m_equipmentAttribute] = nullptr;
	addEquipmentAttribute(j, m_headAttribute, character.getEquipment()->getHelment());
	addEquipmentAttribute(j, m_cuirasseAttribute, character.getEquipment()->getCuirasse());
	addEquipmentAttribute(j, m_bootsAttribute, character.getEquipment()->getBoots());

	j[m_weaponAttribute] = character.getWeapon() == nullptr ? boost::uuids::nil_uuid() : character.getWeapon()->getId();
	j[m_characterTypeAttribute] = character.getCharcterType();

	std::ofstream outFile{ m_config->get(ConfigKeys::saveFile) };
	outFile << std::setw(4) << j << std::endl;
}

Character* JsonGameDataProcesser::load()
{
	std::ifstream input{ m_config->get(ConfigKeys::saveFile) };
	
	if (!input.good())
		return nullptr;

	json characterJson;
	input >> characterJson;

	int strength = characterJson[m_attributesAttribute][m_strengthAttribute].get<int>();
	int agility =  characterJson[m_attributesAttribute][m_agilityAttribute].get<int>();
	int level =	   characterJson[m_attributesAttribute][m_levelAttribute].get<int>();
	auto characterType = static_cast<CharacterType>(characterJson[m_characterTypeAttribute].get<int>());

	auto weaponId{ boost::lexical_cast<boost::uuids::uuid>(characterJson[m_weaponAttribute].get<std::string>()) };
	auto weapon{ m_weaponStorage->getWeaponOrDefault(weaponId) };

	auto attributes{ m_attributesFactory->create(weapon, level, strength, agility, characterType) };

	auto head{ getArmor(characterJson, m_headAttribute) };
	auto cuirass{ getArmor(characterJson, m_cuirasseAttribute) };
	auto legs{ getArmor(characterJson, m_bootsAttribute) };

	auto equipment{ new Equipment{head, cuirass, legs} };

	return new Player{ &attributes, equipment, characterType, weapon };
}
