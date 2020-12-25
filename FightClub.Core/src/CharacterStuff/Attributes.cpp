#include "CharacterStuff/Attributes.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			struct Attributes::Impl
			{
				int m_hp{};
				int m_damage{};
				int m_level{};
				int m_stength{};
				int m_agility{};
				int m_stamina{};

				Impl(int hp, int level, int damage, int strength, int agility, int stamina) : 
					m_hp{ hp },
					m_level{ level },
					m_damage{ damage },
					m_stength{ strength },
					m_agility{ agility },
					m_stamina{ stamina }
				{
				}

				~Impl() = default;
			};

			Attributes::Attributes(int hp, int level, int damage, int strength, int agility, int stamina) :
				pImpl{ std::make_unique<Impl>(hp, level, damage, strength, agility, stamina) }
			{
			}

			Attributes::~Attributes() = default;

			int Attributes::getHp() const { return pImpl->m_hp; }
			void Attributes::setHp(int hp) { pImpl->m_hp = hp; }
			int Attributes::getDamage() const { return pImpl->m_damage; }
			int Attributes::getLevel() const { return pImpl->m_level; }
			int Attributes::getStrength() const { return pImpl->m_stength; }
			int Attributes::getAgility() const { return pImpl->m_agility; }
			int Attributes::getStamina() const { return pImpl->m_stamina; }

			std::ostream& operator<<(std::ostream& out, const Attributes& attributes) 
			{
				out << "HP: " << attributes.getHp() << '\n' << "Level: " << attributes.getLevel() << '\n'
					<< "Damage: " << attributes.getDamage() << '\n' << "Strength: " << attributes.getStrength() << '\n'
					<< "Agility: " << attributes.getAgility() << '\n' << "Stamina: " << attributes.getStamina();

				return out;
			}
		}
	}
}