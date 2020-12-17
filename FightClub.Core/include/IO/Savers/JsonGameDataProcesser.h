#pragma once

#include "GameDataProcesser.h"
#include "CharacterStuff/IAttributesFactory.h"
#include "CharacterStuff/Armors/IArmorStorage.h"
#include "CharacterStuff/Weapons/IWeaponStorage.h"
#include "Common/Configs/IConfig.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace fightclub
{
	namespace core
	{
		namespace io
		{
			namespace savers
			{
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

					characterstuff::IAttributesFactory* m_attributesFactory;
					characterstuff::weapons::IWeaponStorage* m_weaponStorage;
					characterstuff::armors::IArmorStorage* m_armorStorage;
					common::configs::IConfig* m_config;

				public:
					JsonGameDataProcesser(characterstuff::IAttributesFactory* attributeFactory,
						characterstuff::weapons::IWeaponStorage* weaponStorage,
						characterstuff::armors::IArmorStorage* armorStorage,
						common::configs::IConfig* config) :
						m_attributesFactory{ attributeFactory },
						m_weaponStorage{ weaponStorage },
						m_armorStorage{ armorStorage },
						m_config{ config }
					{
					}

					std::unique_ptr<characters::Player> load() override;
					void save(characters::Player& player) const override;

				private:
					const characterstuff::armors::Armor* getArmor(characterstuff::Inventory& inventory, json& j, const std::string& attributeName);
					void characterToJson(json& json, characters::Character& character) const;
					void inventoryToJson(json& json, characterstuff::Inventory& inventory) const;
					std::unique_ptr<characterstuff::Inventory> loadInventory(json& saveFileJson);
				};
			}
		}
	}
}