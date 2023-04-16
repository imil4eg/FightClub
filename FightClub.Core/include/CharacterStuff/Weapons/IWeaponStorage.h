#pragma once

#include <memory>

#include "Weapon.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace weapons
			{
				class IWeaponStorage
				{
				public:
					virtual ~IWeaponStorage() noexcept = default;
					virtual std::unique_ptr<Weapon> getWeaponOrDefault(const boost::uuids::uuid& id) const = 0;
					virtual std::unique_ptr<Weapon> getRandomWeapon() const = 0;
				};
			}
		}
	}
}