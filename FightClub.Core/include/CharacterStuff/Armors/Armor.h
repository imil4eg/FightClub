#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <string>
#include <memory>

#include "CharacterStuff/Attributes.h"
#include "CharacterStuff/Armors/ArmorType.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace armors
			{
				class Armor
				{
				private:
					boost::uuids::uuid m_id;
					std::string m_name;
					std::unique_ptr<characterstuff::Attributes> m_attributes;
					characterstuff::armors::ArmorType m_type{};
					int m_armor{};

				public:
					Armor(boost::uuids::uuid id, const std::string& name, characterstuff::armors::ArmorType type, int armor,
						std::unique_ptr<characterstuff::Attributes> attributes = {}) :
						m_id{ id },
						m_name{ name },
						m_attributes{ std::move(attributes) },
						m_type{ type },
						m_armor{ armor }
					{
					}

					Armor(const Armor& armor) :
						m_id{ armor.m_id },
						m_name{ armor.m_name },
						m_type{ armor.m_type },
						m_armor{ armor.m_armor }
					{
					}

					Armor(Armor&& armor) noexcept :
						m_id{ std::move(armor.m_id) },
						m_name{ std::move(armor.m_name) },
						m_attributes{ std::move(armor.m_attributes.get()) },
						m_type{ armor.m_type },
						m_armor{ armor.m_armor }
					{
					}

					Armor(const std::unique_ptr<Armor>&& armor) :
						m_id{ std::move(armor->m_id) },
						m_name{ std::move(armor->m_name) },
						m_attributes{ std::move(armor->m_attributes) },
						m_type{ static_cast<characterstuff::armors::ArmorType>(armor->m_type) },
						m_armor{ armor->m_armor }
					{
					}

					const boost::uuids::uuid getId() const { return m_id; }
					const std::string& getName() const { return m_name; }
					const characterstuff::Attributes* getAttributes() { return m_attributes.get(); }
					characterstuff::armors::ArmorType getType() const { return m_type; }
					int getArmor() const { return m_armor; }

					friend std::ostream& operator<<(std::ostream& out, const Armor& armor);
				};
			}
		}
	}
}