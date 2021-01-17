#pragma once

#include <boost/uuid/uuid.hpp>
#include <vector>
#include <memory>

#include "Ability.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace abilities
			{
				class IAbilitiesStorage
				{
				public:
					virtual ~IAbilitiesStorage() = default;

					virtual std::unique_ptr<Ability> getOrDefault(const boost::uuids::uuid& id) const = 0;
					virtual std::vector<std::unique_ptr<Ability>> get(AbilityType type) const = 0;
				};
			}
		}
	}
}