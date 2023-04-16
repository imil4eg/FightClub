#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <string>
#include <memory>
#include <iostream>

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
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					Armor(boost::uuids::uuid id, const std::string& name, characterstuff::armors::ArmorType type, int armor,
						std::unique_ptr<characterstuff::Attributes> attributes = {});

					Armor(const Armor& armor);

					Armor(Armor&& armor) noexcept;

					Armor(const std::unique_ptr<Armor>&& armor);

					~Armor();

					const boost::uuids::uuid getId() const;
					const std::string& getName() const;
					const characterstuff::Attributes* getAttributes();
					characterstuff::armors::ArmorType getType() const;
					int getArmor() const;

					friend std::ostream& operator<<(std::ostream& out, const Armor& armor);
				};
			}
		}
	}
}