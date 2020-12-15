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

		const armors::Armor* Inventory::getArmorByName(std::string& name)
		{
			return getBy<armors::Armor>(this->m_armors, [name](std::unique_ptr<armors::Armor>& armor)
				{
					return armor->getName() == name;
				});
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

		template<typename T>
		T* Inventory::getBy(std::vector<std::unique_ptr<T>>& container, std::function<bool(std::unique_ptr<T>&) > condition) const
		{
			for (auto& element : container)
			{
				if (condition(element))
				{
					return element.get();
				}
			}

			return nullptr;
		}
	}
}