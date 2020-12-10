#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <iomanip>
#include <fstream>

#include "Characters/Player.h"
#include "Common/Configs/ConfigKeys.h"
#include "IO/Savers/JsonGameDataProcesser.h"

void addEquipmentAttribute(json& j, std::string attributeName, const Armor* armor)
{
	auto equipmentId{ armor == nullptr ? boost::uuids::nil_uuid() : armor->getId() };
	j["equipment"][attributeName] = boost::lexical_cast<std::string>(equipmentId);
}

std::unique_ptr<Armor> JsonGameDataProcesser::getArmor(json& j, const std::string& attributename)
{
	auto id{ j[m_equipmentAttribute][attributename].get<std::string>() };

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

	auto weaponId{ character.getWeapon() == nullptr ? boost::uuids::nil_uuid() : character.getWeapon()->getId() };
	j[m_weaponAttribute] = boost::lexical_cast<std::string>(weaponId);
	j[m_characterTypeAttribute] = character.getCharcterType();

	std::ofstream outFile{ m_config->get(ConfigKeys::saveFile) };
	outFile << std::setw(4) << j << std::endl;
}

std::unique_ptr<Character> JsonGameDataProcesser::load()
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

	auto attributes{ m_attributesFactory->create(weapon.get(), level, strength, agility, characterType) };

	auto head{ getArmor(characterJson, m_headAttribute) };
	auto cuirass{ getArmor(characterJson, m_cuirasseAttribute) };
	auto legs{ getArmor(characterJson, m_bootsAttribute) };

	auto equipment{ std::make_unique<Equipment>(std::move(head), std::move(cuirass), std::move(legs)) };

	return std::make_unique<Player>(std::move(attributes), std::move(equipment), characterType, std::move(weapon));
}

std::unique_ptr<Character> JsonGameDataProcesser::loadCharacter(json saveFileJson)
{
	int strength = saveFileJson[m_attributesAttribute][m_strengthAttribute].get<int>();
	int agility =  saveFileJson[m_attributesAttribute][m_agilityAttribute].get<int>();	
	int level =	   saveFileJson[m_attributesAttribute][m_levelAttribute].get<int>();
	auto characterType = static_cast<CharacterType>(saveFileJson[m_characterTypeAttribute].get<int>());

	auto weaponId{ boost::lexical_cast<boost::uuids::uuid>(saveFileJson[m_weaponAttribute].get<std::string>()) };
	auto weapon{ m_weaponStorage->getWeaponOrDefault(weaponId) };

	auto attributes{ m_attributesFactory->create(weapon.get(), level, strength, agility, characterType) };

	auto head{    getArmor(saveFileJson, m_headAttribute) };
	auto cuirass{ getArmor(saveFileJson, m_cuirasseAttribute) };
	auto legs{    getArmor(saveFileJson, m_bootsAttribute) };

	auto equipment{ std::make_unique<Equipment>(std::move(head), std::move(cuirass), std::move(legs)) };

	return std::make_unique<Player>(std::move(attributes), std::move(equipment), characterType, std::move(weapon));
}

//std::vector<std::unique_ptr<Armor>> JsonGameDataProcesser::loadInventory(json saveFile)
//{
//	std::vector<std::unique_ptr<Armor>> armors{};
//	for (auto& armor : saveFile["inventory"].items())
//	{
//		m_armorStorage->getOrDefault(boost::lexical_cast<boost::uuids::uuid>(saveFile[""])
//	}
//}
