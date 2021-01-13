#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <iomanip>
#include <fstream>

#include "Characters/Player.h"
#include "CharacterStuff/Abilities/DynamicAbilitiesContainer.h"
#include "Common/Configs/ConfigKeys.h"
#include "IO/Savers/JsonGameDataProcesser.h"
#include "IO/JsonAttributes.h"

namespace fightclub
{
	namespace core
	{
		namespace io
		{
			namespace savers
			{
				struct JsonGameDataProcesser::Impl 
				{
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
					characterstuff::abilities::IAbilitiesStorage* m_abilitiesStorage;
					common::configs::IConfig* m_config;

					Impl(characterstuff::IAttributesFactory& attributeFactory,
						characterstuff::weapons::IWeaponStorage& weaponStorage,
						characterstuff::armors::IArmorStorage& armorStorage,
						characterstuff::abilities::IAbilitiesStorage& abilitiesStorage,
						common::configs::IConfig& config) : 
						m_attributesFactory{&attributeFactory},
						m_weaponStorage{&weaponStorage},
						m_armorStorage{ &armorStorage },
						m_abilitiesStorage{ &abilitiesStorage },
						m_config{ &config }
					{
					}

					void addEquipmentAttribute(json& j, const std::string& attributeName, const characterstuff::armors::Armor* armor) const
					{
						auto equipmentId{ armor == nullptr ? boost::uuids::nil_uuid() : armor->getId() };
						j["equipment"][attributeName] = boost::lexical_cast<std::string>(equipmentId);
					}

					const characterstuff::armors::Armor* getArmor(characterstuff::Inventory& inventory, json& j, const std::string& attributename)
					{
						auto id{ boost::lexical_cast<boost::uuids::uuid>(j[m_equipmentAttribute][attributename].get<std::string>()) };

						return inventory.getArmorById(id);
					}

					void characterToJson(json& json, characters::Character& character) const
					{
						json[m_attributesAttribute] = nullptr;
						json[m_attributesAttribute][m_strengthAttribute] = character.getAttributes()->getStrength();
						json[m_attributesAttribute][m_agilityAttribute] = character.getAttributes()->getAgility();
						json[m_attributesAttribute][m_levelAttribute] = character.getAttributes()->getLevel();

						json[m_equipmentAttribute] = nullptr;
						addEquipmentAttribute(json, m_headAttribute, character.getEquipment().getHelmet());
						addEquipmentAttribute(json, m_cuirasseAttribute, character.getEquipment().getCuirasse());
						addEquipmentAttribute(json, m_bootsAttribute, character.getEquipment().getBoots());

						auto weaponId{ character.getWeapon() == nullptr ? boost::uuids::nil_uuid() : character.getWeapon()->getId() };
						json[m_weaponAttribute] = boost::lexical_cast<std::string>(weaponId);
						json[m_characterTypeAttribute] = character.getCharcterType();
					}

					void inventoryToJson(json& json, characterstuff::Inventory& inventory) const
					{
						std::vector<boost::uuids::uuid> itemIds{};
						for (auto& weapon : inventory.getWeapons())
						{
							itemIds.push_back(weapon->getId());
						}

						json[io::JsonAttributes::Weapons] = itemIds;

						itemIds.clear();

						for (auto& armor : inventory.getArmors())
						{
							itemIds.push_back(armor->getId());
						}

						json[io::JsonAttributes::Armors] = itemIds;
					}

					std::unique_ptr<characterstuff::Inventory> loadInventory(json& saveFile)
					{
						auto inventory{ std::make_unique<characterstuff::Inventory>() };
						for (auto& armor : saveFile[io::JsonAttributes::Armors].items())
						{
							auto armorId{ boost::lexical_cast<boost::uuids::uuid>(armor.value()[io::JsonAttributes::Id].get<std::string>()) };
							inventory->getArmors().push_back(std::move(m_armorStorage->getOrDefault(armorId)));
						}

						for (auto& weapon : saveFile[io::JsonAttributes::Weapons].items())
						{
							auto weaponId{ boost::lexical_cast<boost::uuids::uuid>(weapon.value()[io::JsonAttributes::Id].get<std::string>()) };
							inventory->getWeapons().push_back(std::move(m_weaponStorage->getWeaponOrDefault(weaponId)));
						}

						return inventory;
					}

					void abilitiesToJson(json& json, const characterstuff::abilities::AbilitiesContainer& abilitiesContainer)
					{
						std::vector<std::string> selectedAbilitiesIds;
						for (auto& selectedAbility : abilitiesContainer.getSelected())
						{
							if (selectedAbility == nullptr)
								continue;

							selectedAbilitiesIds.push_back(boost::lexical_cast<std::string>(selectedAbility->getId()));
						}

						json[io::JsonAttributes::SelectedAbilities] = selectedAbilitiesIds;

						std::vector<std::string> characterAbilitiesIds;
						for (auto& ability : abilitiesContainer.getAll())
						{
							characterAbilitiesIds.push_back(boost::lexical_cast<std::string>(ability->getId()));
						}

						json[io::JsonAttributes::Abilities] = characterAbilitiesIds;
					}

					std::unique_ptr<characterstuff::abilities::DynamicAbilitiesContainer> loadAbilities(json& saveFile)
					{
						std::vector<std::unique_ptr<characterstuff::abilities::Ability>> abilities;
						if (saveFile.contains(io::JsonAttributes::Abilities))
						{
							for (auto& abilityIdJson : saveFile[io::JsonAttributes::Abilities].items())
							{
								auto abilityId{ 
									boost::lexical_cast<boost::uuids::uuid>(
										abilityIdJson.value().get<std::string>()) };
								abilities.push_back(m_abilitiesStorage->getOrDefault(abilityId));
							}
						}

						characterstuff::abilities::DynamicAbilitiesContainer::selectedAbilityIds_t selectedAbilities;
						int abilityIdIndex{};
						if (saveFile.contains(io::JsonAttributes::SelectedAbilities))
						{
							for (auto& selectedAbilityIdJson : saveFile[io::JsonAttributes::SelectedAbilities].items())
							{
								auto selectedAbilityId{
									boost::lexical_cast<boost::uuids::uuid>(
										selectedAbilityIdJson.value().get<std::string>()) };
								selectedAbilities[abilityIdIndex] = selectedAbilityId;
								abilities.push_back(m_abilitiesStorage->getOrDefault(selectedAbilityId));

								++abilityIdIndex;
							}
						}

						return std::make_unique<characterstuff::abilities::DynamicAbilitiesContainer>(std::move(abilities), selectedAbilities);
					}
				};

				JsonGameDataProcesser::JsonGameDataProcesser(characterstuff::IAttributesFactory& attributeFactory,
					characterstuff::weapons::IWeaponStorage& weaponStorage,
					characterstuff::armors::IArmorStorage& armorStorage,
					characterstuff::abilities::IAbilitiesStorage& abilitiesStorage,
					common::configs::IConfig& config) :
					pImpl(std::make_unique<Impl>(attributeFactory, weaponStorage, armorStorage, abilitiesStorage, config))
				{
				}

				JsonGameDataProcesser::~JsonGameDataProcesser() = default;

				void JsonGameDataProcesser::save(characters::Player& player) const
				{
					json j;

					pImpl->characterToJson(j, player);
					pImpl->inventoryToJson(j, player.getInventory());
					pImpl->abilitiesToJson(j, player.getAbilitiesContainer());

					std::ofstream outFile{ pImpl->m_config->get(common::configs::ConfigKeys::saveFile) };
					outFile << std::setw(4) << j << std::endl;
				}

				std::unique_ptr<characters::Player> JsonGameDataProcesser::load()
				{
					std::ifstream input{ pImpl->m_config->get(common::configs::ConfigKeys::saveFile) };

					if (!input.good())
						return nullptr;

					json characterJson;
					input >> characterJson;

					int strength = characterJson[pImpl->m_attributesAttribute][pImpl->m_strengthAttribute].get<int>();
					int agility = characterJson[pImpl->m_attributesAttribute][pImpl->m_agilityAttribute].get<int>();
					int level = characterJson[pImpl->m_attributesAttribute][pImpl->m_levelAttribute].get<int>();
					auto characterType = static_cast<characters::CharacterType>(characterJson[pImpl->m_characterTypeAttribute].get<int>());

					auto inventory{ pImpl->loadInventory(characterJson) };

					auto weaponId{ boost::lexical_cast<boost::uuids::uuid>(characterJson[pImpl->m_weaponAttribute].get<std::string>()) };
					auto weapon{ inventory->getWeaponById(weaponId) };

					auto attributes{ pImpl->m_attributesFactory->create(weapon, level, strength, agility, characterType) };

					auto head{ pImpl->getArmor(*inventory.get(), characterJson, pImpl->m_headAttribute) };
					auto cuirass{ pImpl->getArmor(*inventory.get(), characterJson, pImpl->m_cuirasseAttribute) };
					auto legs{ pImpl->getArmor(*inventory.get(), characterJson, pImpl->m_bootsAttribute) };

					auto equipment{ std::make_unique<characterstuff::DynamicEquipment>(head, cuirass, legs) };

					auto abilities{ pImpl->loadAbilities(characterJson) };

					return std::make_unique<characters::Player>(std::move(attributes), std::move(equipment), characterType, 
						std::move(inventory), std::move(abilities), weapon);
				}
			}
		}
	}
}