#include "CharacterModel.hpp"

namespace FightClub::Server::Common {

    CharacterModel::CharacterModel(int id, CharacterType type, int userId,
                                 AttributeModelPtr attribute, 
                                const ArmorModel* head, const ArmorModel* cuirass,
                                const ArmorModel* boots, const WeaponModel* weapon, 
                                AbilityModelPtrArray&& abilities,
                                InventoryModelPtr inventory) :
                                m_id(id),
                                m_type(type),
                                m_userId(userId),
                                m_attribute(std::move(attribute)),
                                m_head(head),
                                m_cuirass(cuirass),
                                m_boots(boots),
                                m_weapon(weapon),
                                m_abilities(std::move(abilities)),
                                m_inventory(std::move(inventory)),
                                m_damage(CharacterConstants::DefaultDamage)
    {
        m_damage += (((type == Common::CharacterType::strong) ?
                        m_attribute->getStrength() :
                        m_attribute->getAgility()) * Common::CharacterConstants::BonusDamageForMainAttributeMultiplier);
        if (m_weapon != nullptr)
        {
            m_damage += m_weapon->getDamage();
        }
    }

}