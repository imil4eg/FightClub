#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace fightclub
{
	namespace characterstuff
	{
		namespace weapons
		{
			class Weapon
			{
			private:
				boost::uuids::uuid m_id{};
				std::string m_name{};
				int m_damage{};

			public:
				Weapon(boost::uuids::uuid& uuid, std::string& name, int damage) :
					m_id{ uuid },
					m_name{ name },
					m_damage{ damage }
				{
				}

				Weapon(Weapon& weapon) :
					m_id{ weapon.m_id },
					m_name{ weapon.m_name },
					m_damage{ weapon.m_damage }
				{
				}

				Weapon(Weapon&& weapon) noexcept :
					m_id{ std::move(weapon.m_id) },
					m_name{ std::move(weapon.m_name) },
					m_damage{ weapon.m_damage }
				{
				}

				virtual ~Weapon() noexcept = default;
				int getDamage() const { return m_damage; }
				const std::string& getName() const { return m_name; }
				const boost::uuids::uuid& getId() const { return m_id; }

				friend std::ostream& operator<<(std::ostream& out, const Weapon& weapon);
			};
		}
	}
}

#endif // !WEAPON_H

