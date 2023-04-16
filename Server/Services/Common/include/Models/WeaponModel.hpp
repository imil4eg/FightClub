#pragma once

#include <memory>
#include <string>

namespace FightClub {
    namespace Server {
        namespace Common {

            class WeaponModel
            {
            public:
                WeaponModel(int id, const std::string& name, int damage) :
                    m_id(id),
                    m_name(name),
                    m_damage(damage)
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

            inline int getDamage() const
            {
                return m_damage;
            }

            private:
                int m_id;
                std::string m_name;
                int m_damage; 
            };

            using WeaponModelPtr = std::unique_ptr<WeaponModel>;
        }
    }
}