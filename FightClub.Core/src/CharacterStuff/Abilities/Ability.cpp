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
					int m_value;
					int m_duration;

					Impl(std::string name, AbilityType type, int cost, int value, int duration) :
						m_name{ name },
						m_type{ type },
						m_cost{ cost },
						m_value{ value },
						m_duration{ duration }
					{
					}

					Impl(boost::uuids::uuid&& id, std::string&& name, AbilityType type, int cost, int value, int duration) :
						m_id{std::move(id)},
						m_name{std::move(name)},
						m_type{type},
						m_cost{ cost },
						m_value{ value },
						m_duration{duration}
					{
					}

					~Impl() = default;
				};

				Ability::Ability(std::string name, AbilityType type, int cost, int damage, int duration) :
					pImpl{ std::make_unique<Impl>(name, type, cost, damage, duration) }
				{
				}

				Ability::Ability(boost::uuids::uuid&& id, std::string&& name, AbilityType type, int cost, int damage, int duration) :
					pImpl{ std::make_unique<Impl>(std::move(id), std::move(name), type, cost, damage, duration) }
				{
				}

				Ability::~Ability() = default;

				const std::string& Ability::getName() const { return pImpl->m_name; }
				const boost::uuids::uuid& Ability::getId() const { return pImpl->m_id; }
				AbilityType Ability::getType() const { return pImpl->m_type; }
				int Ability::getCost() const { return pImpl->m_cost; }
				int Ability::getValue() const { return pImpl->m_value; }
				int Ability::getDuration() const { return pImpl->m_duration; }
			}
		}
	}
}