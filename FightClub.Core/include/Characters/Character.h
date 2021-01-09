#pragma once

#include <array>
#include <memory>
#include <iostream>

#include "CharacterType.h"
#include "CharacterStuff/Attributes.h"
#include "CharacterStuff/Equipment.h"
#include "CharacterStuff/Abilities/AbilitiesContainer.h"
#include "CharacterStuff/Weapons/Weapon.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			class Character
			{
			private:
				typedef core::characterstuff::abilities::AbilitiesContainer abilitiesCointainer_t;

				struct Impl;
				std::unique_ptr<Impl> pImpl;

			public:
				Character(std::unique_ptr<characterstuff::Attributes> attributes, std::unique_ptr<characterstuff::Equipment> equipment,
						  std::unique_ptr<abilitiesCointainer_t> abilities, CharacterType characterType);

				Character(Character&& character) noexcept;

				Character(std::unique_ptr<Character> character);

				virtual ~Character();

				characterstuff::Attributes* getAttributes() const;
				void updateAttributes(std::unique_ptr<characterstuff::Attributes> attributes);
				characterstuff::Equipment& getEquipment() const;
				abilitiesCointainer_t& getAbilitiesContainer() const;
				virtual const characterstuff::weapons::Weapon* const getWeapon() const = 0;
				CharacterType getCharcterType() const;

				void restoreHp();

				friend std::ostream& operator<<(std::ostream& out, const Character& character);
			};
		}
	}
}