#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <iomanip>
#include <fstream>

#include "Characters/Player.h"
#include "Common/Configs/ConfigKeys.h"
#include "IO/Savers/JsonGameDataProcesser.h"
#include "IO/JsonAttributes.h"

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

void JsonGameDataProcesser::save(fightclub::models::UserDataModel& userDataModel) const
{
	json j;

	characterToJson(j, *userDataModel.character);
	inventoryToJson(j, userDataModel);

	std::ofstream outFile{ m_config->get(ConfigKeys::saveFile) };
	outFile << std::setw(4) << j << std::endl;
}

void JsonGameDataProcesser::characterToJson(json& json, Character& character) const
{
	json[m_attributesAttribute] = nullptr;
	json[m_attributesAttribute][m_strengthAttribute] = character.getAttributes()->getStrength();
	json[m_attributesAttribute][m_agilityAttribute] =  character.getAttributes()->getAgility();
	json[m_attributesAttribute][m_levelAttribute] =    character.getAttributes()->getLevel();
	 
	json[m_equipmentAttribute] = nullptr;
	addEquipmentAttribute(json, m_headAttribute,	  character.getEquipment()->getHelment());
	addEquipmentAttribute(json, m_cuirasseAttribute, character.getEquipment()->getCuirasse());
	addEquipmentAttribute(json, m_bootsAttribute,	  character.getEquipment()->getBoots());

	auto weaponId{ character.getWeapon() == nullptr ? boost::uuids::nil_uuid() : character.getWeapon()->getId() };
	json[m_weaponAttribute] = boost::lexical_cast<std::string>(weaponId);
	json[m_characterTypeAttribute] = character.getCharcterType();
}

void JsonGameDataProcesser::inventoryToJson(json& json, fightclub::models::UserDataModel& userDataModel) const
{
	std::vector<boost::uuids::uuid> itemIds{};
	for (auto& weapon : userDataModel.weapons)
	{
		itemIds.push_back(weapon->getId());
	}

	json[fightclub::io::JsonAttributes::Weapons] = itemIds;

	itemIds.clear();

	for (auto& armor : userDataModel.armors)
	{
		itemIds.push_back(armor->getId());
	}

	json[fightclub::io::JsonAttributes::Armors] = itemIds;
}

std::unique_ptr<fightclub::models::UserDataModel> JsonGameDataProcesser::load()
{
	std::ifstream input{ m_config->get(ConfigKeys::saveFile) };
	
	if (!input.good())
		return nullptr;

	json characterJson;
	input >> characterJson;

	auto userDataModel{ std::make_unique<fightclub::models::UserDataModel>() };
	userDataModel->character = loadCharacter(characterJson);
	loadInventory(*userDataModel, characterJson);

	return userDataModel;
}

std::unique_ptr<Character> JsonGameDataProcesser::loadCharacter(json& saveFileJson)
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

void JsonGameDataProcesser::loadInventory(fightclub::models::UserDataModel& userDataModel, json& saveFile)
{
	std::vector<std::unique_ptr<Armor>> armors{};
	for (auto& armor : saveFile["inventory"][fightclub::io::JsonAttributes::Armors].items())
	{
		auto armorId{ boost::lexical_cast<boost::uuids::uuid>(armor.value()[fightclub::io::JsonAttributes::Id].get<std::string>()) };
		userDataModel.armors.push_back(std::move(m_armorStorage->getOrDefault(armorId)));
	}

	for (auto& weapon : saveFile["inventory"][fightclub::io::JsonAttributes::Weapons].items())
	{
		auto weaponId{ boost::lexical_cast<boost::uuids::uuid>(weapon.value()[fightclub::io::JsonAttributes::Id].get<std::string>()) };
		userDataModel.weapons.push_back(std::move(m_weaponStorage->getWeaponOrDefault(weaponId)));
	}
}
