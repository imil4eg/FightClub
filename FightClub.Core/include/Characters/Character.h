#pragma once

#include <memory>

#include "CharacterType.h"
#include "CharacterStuff/Attributes.h"
#include "CharacterStuff/Equipment.h"
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
				struct Impl;
				std::unique_ptr<Impl> pImpl;

			public:
				Character(std::unique_ptr<characterstuff::Attributes> attributes, std::unique_ptr<characterstuff::Equipment> equipment,
						  CharacterType characterType);

				Character(Character&& character) noexcept;

				Character(std::unique_ptr<Character> character);

				virtual ~Character();

				characterstuff::Attributes* getAttributes() const;
			    characterstuff::Equipment& getEquipment() const;
				virtual const characterstuff::weapons::Weapon* const getWeapon() const = 0;
				CharacterType getCharcterType() const;

				void restoreHp();
			};
		}
	}
}