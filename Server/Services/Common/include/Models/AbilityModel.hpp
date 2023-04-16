#pragma once

#include <memory>
#include <vector>
#include <string>

namespace FightClub {
    namespace Server {
        namespace Common {

            class AbilityModel
            {
            public:
                enum class AbilityType 
                {
                    damageBoost,
                    armorBoost,
                    trap,
                    maxAbilityType
                };

            public:
                AbilityModel(int id, const std::string& name, int cost, int value, int duration, AbilityType abilityType) :
                    m_id(id),
                    m_name(name),
                    m_cost(cost),
                    m_value(value),
                    m_duration(duration),
                    m_abilityType(abilityType)
                {
                }

                inline int getId() const
                {
                    return m_id;
                }

                inline const std::string& getName() const
                {
                    return m_name;
                }

                inline int getCost() const
                {
                    return m_cost;
                }

                inline int getValue() const
                {
                    return m_value;
                }

                inline int getDuration() const
                {
                    return m_duration;
                }

                inline AbilityType getAbilityType() const
                {
                    return m_abilityType;
                }

            private:
                int m_id;
                std::string m_name;
                int m_cost;
                int m_value;
                int m_duration;
                AbilityType m_abilityType;
            };

            using AbilityModelPtr = std::unique_ptr<AbilityModel>;
            using AbilityModelPtrArray = std::vector<AbilityModelPtr>;
        }
    }
}