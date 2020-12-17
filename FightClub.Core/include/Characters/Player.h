#pragma once

#include "Characters/Character.h"
#include "CharacterStuff/Inventory.h"
#include "CharacterStuff/DynamicEquipment.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			class Player : public Character
			{
			private:
				std::unique_ptr<characterstuff::Inventory> m_inventory{};
				std::unique_ptr<characterstuff::DynamicEquipment> m_equipment;
				const characterstuff::weapons::Weapon* m_weapon;

			public:
				Player(std::unique_ptr<characterstuff::Attributes> attributes,
					std::unique_ptr<characterstuff::DynamicEquipment> equipment,
					CharacterType characterType,
					std::unique_ptr<characterstuff::Inventory> inventory,
					const characterstuff::weapons::Weapon* weapon = nullptr) :
					Character{ std::move(attributes), characterType },
					m_inventory{ std::move(inventory) },
					m_equipment{ std::move(equipment) },
					m_weapon{ weapon }
				{
				}

				Player(std::unique_ptr<Character>&& character, std::unique_ptr<characterstuff::Inventory>&& inventory,
					std::unique_ptr<characterstuff::DynamicEquipment>&& equipment, const characterstuff::weapons::Weapon* weapon) :
					Character{ std::move(character) },
					m_inventory{ std::move(inventory) },
					m_equipment{ std::move(equipment) },
					m_weapon{ weapon }
				{
				}

				characterstuff::Inventory& getInventory() { return *m_inventory.get(); }
				characterstuff::Equipment* getEquipment() const override { return m_equipment.get(); }

				void playTurn(Character& target) override;
				void hit(Character& enemy, battle::HitDirection hitDirection) override;
				const characterstuff::weapons::Weapon* const getWeapon() const override { return m_weapon; }
				void changeWeapon(characterstuff::weapons::Weapon* weapon) { m_weapon = weapon; }
			};
		}
	}
}