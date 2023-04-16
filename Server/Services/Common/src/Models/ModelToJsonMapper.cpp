#include "ModelToJsonMapper.hpp"

#include "JsonAttributes.hpp"
#include "JsonHelpers.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            json AttributeToJson(const AttributeModel& model)
            {
                json json;
                json.emplace(Common::JsonAttributes::ID, model.getId());
                json.emplace(Common::JsonAttributes::level, model.getLevel());
                json.emplace(Common::JsonAttributes::health, model.getHealth());
                json.emplace(Common::JsonAttributes::stamina, model.getStamina());
                json.emplace(Common::JsonAttributes::strength, model.getStrength());
                json.emplace(Common::JsonAttributes::agility, model.getAgility());

                return json;
            }

            json ArmorToJson(const ArmorModel& model)
            {
                json armorJson;
                armorJson.emplace(Common::JsonAttributes::ID, model.getId());
                
                json attributeJson = AttributeToJson(*model.getAttribute());
                armorJson.emplace(Common::JsonAttributes::attribute, attributeJson);

                armorJson.emplace(Common::JsonAttributes::armorType, static_cast<int>(model.getArmorType()));
                armorJson.emplace(Common::JsonAttributes::name, model.getName());
                armorJson.emplace(Common::JsonAttributes::armor, model.getArmor());

                return armorJson;
            }

            json WeaponToJson(const WeaponModel& model)
            {
                json json;
                json.emplace(Common::JsonAttributes::ID, model.getId());
                json.emplace(Common::JsonAttributes::name, model.getName());
                json.emplace(Common::JsonAttributes::damage, model.getDamage());

                return json;
            }

            json InventoryToJson(const InventoryModel& model)
            {
                json armors;
                for (auto it = model.armorBegin(); it != model.armorEnd(); ++it)
                {
                    armors.emplace_back(ArmorToJson(*it->second));
                }

                json weapons;
                for (auto it = model.weaponBegin(); it != model.weaponEnd(); ++it)
                {
                    weapons.emplace_back(WeaponToJson(*it->second));
                }

                json result;

                if (armors.size() > 0)
                    result.emplace(Common::JsonAttributes::armors, armors);
                
                if (weapons.size() > 0)
                    result.emplace(Common::JsonAttributes::weapons, weapons);

                return result;
            }

            json AbilityToJson(const AbilityModel& model)
            {
                json ability;
                ability.emplace(Common::JsonAttributes::ID, model.getId());
                ability.emplace(Common::JsonAttributes::name, model.getName());
                ability.emplace(Common::JsonAttributes::cost, model.getCost());
                ability.emplace(Common::JsonAttributes::value, model.getValue());
                ability.emplace(Common::JsonAttributes::duration, model.getDuration());
                ability.emplace(Common::JsonAttributes::abilityType, static_cast<int>(model.getAbilityType()));

                return ability;
            }

            template<typename InputIterator>
            json AbilitiesToJson(InputIterator begin, InputIterator end)
            {
                json abilities;
                for (auto it = begin; it != end; ++it)
                {
                    abilities.emplace_back(AbilityToJson(*it->get()));
                }

                return abilities;
            }

            json AbilitiesToJson(const AbilityModelPtrArray& abilities)
            {
                return AbilitiesToJson(abilities.cbegin(), abilities.cend());
            }

            json CharacterToJson(const CharacterModel& character)
            {
                json data;
                data.emplace(JsonAttributes::ID, character.getId());
                data.emplace(JsonAttributes::characterType, static_cast<int>(character.getType()));
                data.emplace(JsonAttributes::userId, character.getUserId());
                data.emplace(JsonAttributes::damage, character.getDamage());

                data.emplace(JsonAttributes::attribute, Common::AttributeToJson(character.getAttribute()));
                Common::emplaceIDIfNotNull<Common::ArmorModel>(data, JsonAttributes::headId, character.getHead());
                Common::emplaceIDIfNotNull<Common::ArmorModel>(data, JsonAttributes::cuirassId, character.getCuirass());
                Common::emplaceIDIfNotNull<Common::ArmorModel>(data, JsonAttributes::bootsId, character.getBoots());
                Common::emplaceIDIfNotNull<Common::WeaponModel>(data, JsonAttributes::weaponId, character.getWeapon());
                data.emplace(JsonAttributes::inventory, Common::InventoryToJson(character.getInventory()));
                
                const Common::AbilityModelPtrArray& abilities = character.getAbilities();
                data.emplace(JsonAttributes::abilities, Common::AbilitiesToJson(abilities.cbegin(), abilities.cend()));
            
                return data;
            }

            AttributeModelPtr JsonToAttribute(const json& json)
            {
                return std::make_unique<AttributeModel>(json[JsonAttributes::ID].get<int>(), json[JsonAttributes::level].get<int>(), json[JsonAttributes::strength].get<int>(), json[JsonAttributes::agility].get<int>());
            }

            ArmorModelPtr JsonToArmor(const json& data)
            {
                auto attribute = JsonToAttribute(data[JsonAttributes::attribute]);

                return std::make_unique<ArmorModel>(data[JsonAttributes::ID].get<int>(),
                                                     std::move(attribute), data[JsonAttributes::armorType].get<ArmorModel::ArmorType>(),
                                                      data[JsonAttributes::name].get<std::string>(), data[JsonAttributes::armor].get<int>());
            }

            WeaponModelPtr JsonToWeapon(const json& data)
            {
                return std::make_unique<WeaponModel>(data[JsonAttributes::ID].get<int>(), data[JsonAttributes::name].get<std::string>(),
                                                     data[JsonAttributes::damage].get<int>());
            }

            InventoryModelPtr JsonToInventory(const json& data)
            {
                std::vector<ArmorModelPtr> armors;
                json armorsJson = data[JsonAttributes::armors];
                for (json::iterator it = armorsJson.begin(); it != armorsJson.end(); ++it)
                {
                    armors.push_back(JsonToArmor(*it));
                }

                std::vector<WeaponModelPtr> weapons;
                json weaponsJson = data[JsonAttributes::weapons];
                for (json::iterator it = weaponsJson.begin(); it != weaponsJson.end(); ++it)
                {
                    weapons.push_back(JsonToWeapon(*it));
                }

                return std::make_unique<InventoryModel>(armors.begin(), armors.end(), weapons.begin(), weapons.end());
            }

            AbilityModelPtr JsonToAbility(const json& data)
            {
                return std::make_unique<AbilityModel>(data[JsonAttributes::ID].get<int>(), data[JsonAttributes::name].get<std::string>(),
                                                    data[JsonAttributes::cost].get<int>(), data[JsonAttributes::value].get<int>(), data[JsonAttributes::duration].get<int>(),
                                                    data[JsonAttributes::abilityType].get<AbilityModel::AbilityType>());
            }

            AbilityModelPtrArray JsonToAbilities(const json& data)
            {
                AbilityModelPtrArray abilities;

                for (auto it = data.begin(); it != data.end(); ++it)
                {
                    abilities.push_back(JsonToAbility(*it));
                }

                return abilities;
            }            

            CharacterModelPtr JsonToCharacter(const json& json)
            {
                auto attribute = JsonToAttribute(json[JsonAttributes::attribute]);
                auto inventory = JsonToInventory(json[JsonAttributes::inventory]);
                auto abilities = JsonToAbilities(json[JsonAttributes::abilities]);
                
                return std::make_unique<CharacterModel>(json[JsonAttributes::ID].get<int>(), json[JsonAttributes::characterType].get<CharacterType>(), 
                                    json[JsonAttributes::userId].get<int>(), std::move(attribute),
                                    getInventoryItemByIdOrNullptr<ArmorModel>(*inventory.get(), json, JsonAttributes::headId),
                                    getInventoryItemByIdOrNullptr<ArmorModel>(*inventory.get(), json, JsonAttributes::cuirassId),
                                    getInventoryItemByIdOrNullptr<ArmorModel>(*inventory.get(), json, JsonAttributes::bootsId),
                                    getInventoryItemByIdOrNullptr<WeaponModel>(*inventory.get(), json, JsonAttributes::weaponId),
                                    std::move(abilities),
                                    std::move(inventory));
            }
        }
    }
}