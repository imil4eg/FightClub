#include "CharacterStuff/Abilities/Ability.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace abilities
			{
				struct Ability::Impl
				{
					boost::uuids::uuid m_id;
					std::string m_name;
					AbilityType m_type;
					int m_cost;
					int m_damage;

					Impl(std::string name, AbilityType type, int cost, int damage) :
						m_name{ name }, m_type{ type }, m_cost{ cost }, m_damage{ damage }
					{
					}

					Impl(boost::uuids::uuid&& id, std::string&& name, AbilityType type, int cost, int damage) :
						m_id{std::move(id)},
						m_name{std::move(name)},
						m_type{type},
						m_cost{ cost },
						m_damage{ damage }
					{
					}

					~Impl() = default;
				};

				Ability::Ability(std::string name, AbilityType type, int cost, int damage) :
					pImpl{ std::make_unique<Impl>(name, type, cost, damage) }
				{
				}

				Ability::Ability(boost::uuids::uuid&& id, std::string&& name, AbilityType type, int cost, int damage) :
					pImpl{ std::make_unique<Impl>(std::move(id), std::move(name), type, cost, damage) }
				{
				}

				Ability::~Ability() = default;

				const std::string& Ability::getName() const { return pImpl->m_name; }
				const boost::uuids::uuid& Ability::getId() const { return pImpl->m_id; }
				AbilityType Ability::getType() const { return pImpl->m_type; }
				int Ability::getCost() const { return pImpl->m_cost; }
				int Ability::getDamage() const { return pImpl->m_damage; }
			}
		}
	}
}