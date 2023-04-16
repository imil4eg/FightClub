#include "Characters/Player.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			struct Player::Impl
			{
				std::unique_ptr<characterstuff::Inventory> m_inventory{};
				const characterstuff::weapons::Weapon* m_weapon;
				
				Impl(std::unique_ptr<characterstuff::Inventory> inventory, 
					const characterstuff::weapons::Weapon* weapon) : 
					m_inventory{std::move(inventory)},
					m_weapon{ weapon }
				{
				}
			};

			Player::Player(std::unique_ptr<characterstuff::Attributes> attributes,
				std::unique_ptr<characterstuff::DynamicEquipment> equipment,
				CharacterType characterType,
				std::unique_ptr<characterstuff::Inventory> inventory,
				std::unique_ptr<characterstuff::abilities::DynamicAbilitiesContainer> abilitiesContainer,
				const characterstuff::weapons::Weapon* weapon) : 
				Character{ std::move(attributes), std::move(equipment), std::move(abilitiesContainer), characterType },
				pImpl{std::make_unique<Impl>(std::move(inventory),weapon) }
			{
			}

			Player::~Player() = default;

			characterstuff::Inventory& Player::getInventory() { return *pImpl->m_inventory.get(); }
			
			const characterstuff::weapons::Weapon* const Player::getWeapon() const { return pImpl->m_weapon; }
			void Player::changeWeapon(characterstuff::weapons::Weapon* weapon) { pImpl->m_weapon = weapon; }
		}
	}
}