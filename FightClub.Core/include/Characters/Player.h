#pragma once

#include "Characters/Character.h"
#include "CharacterStuff/Abilities/Ability.h"
#include "CharacterStuff/Inventory.h"
#include "CharacterStuff/DynamicEquipment.h"
#include "CharacterStuff/Abilities/DynamicAbilitiesContainer.h"

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
					std::unique_ptr<characterstuff::abilities::DynamicAbilitiesContainer> abilitiesContainer,
					const characterstuff::weapons::Weapon* weapon = nullptr);

				~Player();

				characterstuff::Inventory& getInventory();
				
				const characterstuff::weapons::Weapon* const getWeapon() const override;
				void changeWeapon(characterstuff::weapons::Weapon* weapon);
			};
		}
	}
}