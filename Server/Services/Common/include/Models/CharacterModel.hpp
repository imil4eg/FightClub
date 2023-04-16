#pragma once

#include <memory>
#include <vector>

#include "AbilityModel.hpp"
#include "AttributeModel.hpp"
#include "ArmorModel.hpp"
#include "CharacterConstants.hpp"
#include "InventoryModel.hpp"
#include "WeaponModel.hpp"

namespace FightClub::Server::Common {

            enum class CharacterType
            {
                strong,
                agility,
                max_character_type
            };

            class CharacterModel
            {
            public:
                CharacterModel(int id, CharacterType type, int userId,
                                 AttributeModelPtr attribute, 
                                const ArmorModel* head, const ArmorModel* cuirass,
                                const ArmorModel* boots, const WeaponModel* weapon, 
                                AbilityModelPtrArray&& abilities,
                                InventoryModelPtr inventory);

                CharacterModel(CharacterModel&&) = default;

                CharacterModel(const CharacterModel&) = delete;
                CharacterModel operator=(const CharacterModel&) = delete;

                inline int getId() const
                {
                    return m_id;
                }

                inline int getUserId() const
                {
                    return m_userId;
                }

                inline CharacterType getType() const
                {
                    return m_type;
                }

                inline const AttributeModel& getAttribute() const
                {
                    return *m_attribute.get();
                }

                inline const ArmorModel* getHead() const
                {
                    return m_head;
                }

                inline const ArmorModel* getCuirass() const
                {
                    return m_cuirass;
                }

                inline const ArmorModel* getBoots() const
                {
                    return m_boots;
                }

                inline const WeaponModel* getWeapon() const
                {
                    return m_weapon;
                }

                inline const InventoryModel& getInventory() const
                {
                    return *m_inventory.get();
                }

                inline const AbilityModelPtrArray& getAbilities() const
                {
                    return m_abilities;
                }

                inline int getDamage() const
                {
                    return m_damage;
                }

                inline void setHead(ArmorModel* head)
                {
                    m_head = head;
                }

                inline void setCuirass(ArmorModel* cuirass)
                {
                    m_cuirass = cuirass;
                }

                inline void setBoots(ArmorModel* boots)
                {
                    m_boots = boots;
                }

                inline void setWeapon(WeaponModel* weapon)
                {
                    m_weapon = weapon;
                }

                inline void setAbilities(AbilityModelPtrArray&& abilities)
                {
                    m_abilities = std::move(abilities);
                }

            private:
                int m_id;
                CharacterType m_type;
                int m_userId;
                AttributeModelPtr m_attribute;
                const ArmorModel* m_head;
                const ArmorModel* m_cuirass;
                const ArmorModel* m_boots;
                const WeaponModel* m_weapon;
                AbilityModelPtrArray m_abilities;
                InventoryModelPtr m_inventory;
                int m_damage;
            };

            using CharacterModelPtr = std::unique_ptr<CharacterModel>;
}
