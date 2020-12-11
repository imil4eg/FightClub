#include <algorithm>

#include "CharacterStuff/Inventory.h"

namespace fightclub
{
	namespace characterstuff
	{
		const Weapon* const Inventory::getWeaponById(boost::uuids::uuid& id)
		{
			if (id == boost::uuids::nil_uuid())
			{
				return nullptr;
			}

			auto weaponIt{ std::find_if(m_weapons.begin(), m_weapons.end(),
				[id](std::unique_ptr<Weapon>& weapon)
				{
					return weapon->getId() == id;
				}) };

			return weaponIt == m_weapons.end() ? nullptr : weaponIt->get();
		}
	}
}