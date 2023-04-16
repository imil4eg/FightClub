#pragma once

#include <vector>
#include <unordered_map>

#include "ArmorModel.hpp"
#include "WeaponModel.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            class InventoryModel
            {
            public:
                using ArmorPtrArray = std::vector<ArmorModelPtr>;
                using WeaponPtrArray = std::vector<WeaponModelPtr>;
                using DtoArmorPtrStorage = std::unordered_map<int, ArmorModelPtr>;
                using DtoWeaponPtrStorage = std::unordered_map<int, WeaponModelPtr>;

            public:
                template<typename ArmorInputIt, typename WeaponInputIt>
                InventoryModel(ArmorInputIt armorBegin, ArmorInputIt armorEnd, 
                                WeaponInputIt weaponBegin, WeaponInputIt weaponEnd)
                {
                    for (auto armorIt = armorBegin; armorIt != armorEnd; ++armorIt)
                    {
                        m_armors.insert(std::make_pair(armorIt->get()->getId(), std::move(*armorIt)));
                    }

                    for (auto weaponIt = weaponBegin; weaponIt != weaponEnd; ++weaponIt)
                    {
                        m_weapons.insert(std::make_pair(weaponIt->get()->getId(), std::move(*weaponIt)));
                    }
                }

                inline const ArmorModel* getArmorById(int armorId) const
                {
                    auto it = m_armors.find(armorId);
                    if (it == m_armors.end())
                    {
                        return nullptr;
                    }

                    return it->second.get();
                }

                inline const WeaponModel* getWeaponById(int weaponId) const
                {
                    auto it = m_weapons.find(weaponId);
                    if (it == m_weapons.end())
                    {
                        return nullptr;
                    }

                    return it->second.get();
                }

                inline DtoArmorPtrStorage::const_iterator armorBegin() const
                {
                    return m_armors.cbegin();
                }

                inline DtoArmorPtrStorage::const_iterator armorEnd() const
                {
                    return m_armors.cend();
                }

                inline DtoWeaponPtrStorage::const_iterator weaponBegin() const
                {
                    return m_weapons.cbegin();
                }

                inline DtoWeaponPtrStorage::const_iterator weaponEnd() const
                {
                    return m_weapons.cend();
                }

            private:
                DtoArmorPtrStorage m_armors;
                DtoWeaponPtrStorage m_weapons;
            };

            using InventoryModelPtr = std::unique_ptr<InventoryModel>;
        }
    }
}