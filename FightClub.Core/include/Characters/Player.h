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
				struct Impl;
				std::unique_ptr<Impl> pImpl;

			public:
				Player(std::unique_ptr<characterstuff::Attributes> attributes,
					std::unique_ptr<characterstuff::DynamicEquipment> equipment,
					CharacterType characterType,
					std::unique_ptr<characterstuff::Inventory> inventory,
					const characterstuff::weapons::Weapon* weapon = nullptr);

				~Player();

				characterstuff::Inventory& getInventory();
				
				const characterstuff::weapons::Weapon* const getWeapon() const override;
				void changeWeapon(characterstuff::weapons::Weapon* weapon);
			};
		}
	}
}