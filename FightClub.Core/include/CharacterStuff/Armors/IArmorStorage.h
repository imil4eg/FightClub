 #pragma once

#include <boost/uuid/uuid.hpp>
#include <memory>

#include "Armor.h"
#include "ArmorType.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace armors
			{
				class IArmorStorage
				{
				public:
					virtual ~IArmorStorage() = default;

					virtual std::unique_ptr<Armor> getOrDefault(const boost::uuids::uuid& id) = 0;
					virtual std::unique_ptr<Armor> getRandom(ArmorType armorType) = 0;
				};
			}
		}
	}
}