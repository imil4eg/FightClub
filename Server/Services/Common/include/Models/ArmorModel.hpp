#pragma once

#include <memory>
#include <string>

#include "AttributeModel.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            class ArmorModel
            {
            public:
                enum class ArmorType
                {
                    head,
                    cuirass,
                    gloves,
                    boots,
                    max_armor_type
                };

            public:
                ArmorModel(int id, AttributeModelPtr attribute, ArmorType armorType, const std::string& name,
                           int armor) :
                    m_id(id),
                    m_attribute(std::move(attribute)),
                    m_armorType(armorType),
                    m_name(name),
                    m_armor(armor)
                {
                }

                ArmorModel(const ArmorModel& copy) :
                    m_id(copy.m_id),
                    m_attribute(std::make_unique<AttributeModel>(*copy.m_attribute.get())),
                    m_armorType(copy.m_armorType),
                    m_name(copy.m_name),
                    m_armor(copy.m_armor)
                {
                }

                ArmorModel(ArmorModel&&) = default;

                inline int getId() const
                {
                    return m_id;
                }

                inline const AttributeModel* getAttribute() const
                {
                    return m_attribute.get();
                }

                inline ArmorType getArmorType() const
                {
                    return m_armorType;
                }

                inline const std::string& getName() const
                {
                    return m_name;
                }

                inline int getArmor() const
                {
                    return m_armor;
                }

            private:
                int m_id;
                AttributeModelPtr m_attribute;
                ArmorType m_armorType;
                std::string m_name;
                int m_armor;
            };

            using ArmorModelPtr = std::unique_ptr<ArmorModel>;
        }
    }
}