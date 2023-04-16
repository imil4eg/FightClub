#pragma once

#include "AbilityModel.hpp"
#include "AttributeModel.hpp"
#include "ArmorModel.hpp"
#include "CharacterModel.hpp"
#include "InventoryModel.hpp"
#include "JsonDefinitions.hpp"
#include "WeaponModel.hpp"

namespace FightClub::Server::Common {

            json AttributeToJson(const AttributeModel& model);
            json ArmorToJson(const ArmorModel& model);
            json WeaponToJson(const WeaponModel& model);
            json InventoryToJson(const InventoryModel& model);
            json AbilityToJson(const AbilityModel& model);

            template<typename InputIterator>
            json AbilitiesToJson(InputIterator begin, InputIterator end);

            json AbilitiesToJson(const AbilityModelPtrArray& abilities);

            json CharacterToJson(const CharacterModel& character);

            AttributeModelPtr JsonToAttribute(const json& json);
            ArmorModelPtr JsonToArmor(const json& data);
            WeaponModelPtr JsonToWeapon(const json& data);
            InventoryModelPtr JsonToInventory(const json& data);
            AbilityModelPtr JsonToAbility(const json& data);
            AbilityModelPtrArray JsonToAbilities(const json& data);
            CharacterModelPtr JsonToCharacter(const json& json);

            template<typename T>
            const T* getInventoryItemByIdOrNullptr(const InventoryModel& inventory, const json& data, const std::string& jsonAttributeName)
            {
                if (!data.contains(jsonAttributeName))
                {
                    return nullptr;
                }
                else if constexpr (std::is_same<T, ArmorModel>::value)
                {
                    return inventory.getArmorById(data[jsonAttributeName].get<int>());
                }
                else if constexpr (std::is_same<T, WeaponModel>::value)
                {
                    return inventory.getWeaponById(data[jsonAttributeName].get<int>());
                }
            }
}