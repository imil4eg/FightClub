#include <boost/algorithm/string.hpp>

#include "CharacterStuff/Inventory.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			struct Inventory::Impl
			{
				std::vector<std::unique_ptr<armors::Armor>> m_armors{};
				std::vector<std::unique_ptr<weapons::Weapon>> m_weapons{};

				Impl()
				{
				}

				Impl(std::vector<std::unique_ptr<armors::Armor>>&& armors, std::vector<std::unique_ptr<weapons::Weapon>>&& weapons) : 
					m_armors{ std::move(armors) },
					m_weapons{ std::move(weapons) }
				{
				}

				~Impl() = default;

				template<typename T>
				T* getById(std::vector<std::unique_ptr<T>>& container, boost::uuids::uuid& itemId)
				{
					auto it{ std::find_if(container.begin(), container.end(),
						[itemId](std::unique_ptr<T>& item)
						{
							return item->getId() == itemId;
						}) };

					return it == container.end() ? nullptr : it->get();
				}

				template<typename T>
				T* getBy(std::vector<std::unique_ptr<T>>& container, std::function<bool(std::unique_ptr<T>&) > condition) const
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
			};

			Inventory::Inventory() :
				Inventory(std::vector<std::unique_ptr<armors::Armor>>(), std::vector<std::unique_ptr<weapons::Weapon>>())
			{
			}

			Inventory::Inventory(std::vector<std::unique_ptr<armors::Armor>>&& armors, std::vector<std::unique_ptr<weapons::Weapon>>&& weapons) :
				pImpl(std::make_unique<Impl>(std::move(armors), std::move(weapons)))
			{
			}

			Inventory::~Inventory() = default;

			std::vector<std::unique_ptr<armors::Armor>>& Inventory::getArmors() { return pImpl->m_armors; }
			std::vector<std::unique_ptr<weapons::Weapon>>& Inventory::getWeapons() { return pImpl->m_weapons; }

			const characterstuff::weapons::Weapon* const Inventory::getWeaponById(boost::uuids::uuid& id)
			{
				if (id == boost::uuids::nil_uuid())
				{
					return nullptr;
				}

				return pImpl->getById(pImpl->m_weapons, id);
			}

			const armors::Armor* const Inventory::getArmorById(boost::uuids::uuid& id)
			{
				if (id == boost::uuids::nil_uuid())
				{
					return nullptr;
				}

				return pImpl->getById(pImpl->m_armors, id);
			}

			const armors::Armor* Inventory::getArmorByName(std::string& name)
			{
				return pImpl->getBy<armors::Armor>(pImpl->m_armors, [name](std::unique_ptr<armors::Armor>& armor)
					{
						return boost::iequals(armor->getName(), name);
					});
			}
		}
	}
}