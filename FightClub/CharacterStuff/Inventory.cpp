#include <algorithm>

#include "CharacterStuff/Inventory.h"

namespace fightclub
{
	namespace characterstuff
	{
		const characterstuff::weapons::Weapon* const Inventory::getWeaponById(boost::uuids::uuid& id)
		{
			if (id == boost::uuids::nil_uuid())
			{
				return nullptr;
			}

			return getById(m_weapons, id);
		}

		const armors::Armor* const Inventory::getArmorById(boost::uuids::uuid& id)
		{
			if (id == boost::uuids::nil_uuid())
			{
				return nullptr;
			}

			return getById(m_armors, id);
		}

		template<typename T>
		T* Inventory::getById(std::vector<std::unique_ptr<T>>& container, boost::uuids::uuid& itemId)
		{
			auto it{ std::find_if(container.begin(), container.end(),
				[itemId](std::unique_ptr<T>& item)
				{
					return item->getId() == itemId;
				}) };

			return it == container.end() ? nullptr : it->get();
		}
	}
}