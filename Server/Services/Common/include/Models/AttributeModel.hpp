#pragma once

#include <memory>

#include "CharacterConstants.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            class AttributeModel
            {
            public:
                AttributeModel(int id, int level, int strength, int agility) :
                    m_id(id),
                    m_level(level),
                    m_strength(strength),
                    m_agility(agility),
                    m_health(CharacterConstants::DefaultHp + (CharacterConstants::BonusHPForStrengthMultiplier * strength)),
                    m_stamina(CharacterConstants::DefaultStamina + (CharacterConstants::StaminaPerLevelBonus * level))
                {
                }

                inline int getId() const { return m_id; }
                inline int getLevel() const { return m_level; }
                inline int getStrength() const { return m_strength; }
                inline int getAgility() const { return m_agility; }
                inline int getHealth() const { return m_health; }
                inline int getStamina() const { return m_stamina; }

            private:
                int m_id;
                int m_level;
                int m_strength;
                int m_agility;
                int m_health;
                int m_stamina;
            };

            using AttributeModelPtr = std::unique_ptr<AttributeModel>;
        }
    }
}