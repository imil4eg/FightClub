#ifndef ARMOR_H
#define ARMOR_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <memory>

#include "../Attributes.h"
#include "ArmorType.h"

namespace fightclub
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
				std::unique_ptr<Attributes> m_attributes;
				fightclub::characterstuff::armors::ArmorType m_type{};
				int m_armor{};

			public:
				Armor(boost::uuids::uuid id, const std::string& name, fightclub::characterstuff::armors::ArmorType type, int armor, std::unique_ptr<Attributes> attributes = {}) :
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
					m_type{ static_cast<fightclub::characterstuff::armors::ArmorType>(armor->m_type) },
					m_armor{ armor->m_armor }
				{
				}

				const boost::uuids::uuid getId() const { return m_id; }
				const std::string& getName() const { return m_name; }
				const Attributes* getAttributes() { return m_attributes.get(); }
				fightclub::characterstuff::armors::ArmorType getType() const { return m_type; }
				int getArmor() const { return m_armor; }
			};
		}
	}
}

#endif // !ARMOR_H

