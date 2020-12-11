#ifndef JSON_GAME_SAVER_H
#define JSON_GAME_SAVER_H

#include "GameDataProcesser.h"
#include "CharacterStuff/IAttributesFactory.h"
#include "CharacterStuff/Weapons/IWeaponStorage.h"
#include "CharacterStuff/Armors/IArmorStorage.h"
#include "Common/Configs/IConfig.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;


class JsonGameDataProcesser : public GameDataProcesser
{
private:
	const std::string m_headAttribute{ "head" };
	const std::string m_cuirasseAttribute{ "cuirasse" };
	const std::string m_bootsAttribute{ "boots" };
	const std::string m_attributesAttribute{ "attributes" };
	const std::string m_strengthAttribute{ "strength" };
	const std::string m_agilityAttribute{ "agility" };
	const std::string m_levelAttribute{ "level" };
	const std::string m_weaponAttribute{ "weapon" };
	const std::string m_characterTypeAttribute{ "characterType" };
	const std::string m_equipmentAttribute{ "equipment" };

	IAttributesFactory* m_attributesFactory;
	IWeaponStorage* m_weaponStorage;
	IArmorStorage* m_armorStorage;
	IConfig* m_config;

public:
	JsonGameDataProcesser(IAttributesFactory* attributeFactory, 
		IWeaponStorage* weaponStorage,
		IArmorStorage* armorStorage,
		IConfig* config) :
		m_attributesFactory{ attributeFactory },
		m_weaponStorage{weaponStorage},
		m_armorStorage{armorStorage},
		m_config{config}
	{
	}

	std::unique_ptr<Player> load() override;
	void save(Player& player) const override;

private:
	std::unique_ptr<Armor> getArmor(json& j, const std::string& attributeName);
	void characterToJson(json& json, Character& character) const;
	void inventoryToJson(json& json, fightclub::characterstuff::Inventory& inventory) const;
	std::unique_ptr<fightclub::characterstuff::Inventory> loadInventory(json& saveFileJson);
};


#endif // !JSON_GAME_SAVER_H

