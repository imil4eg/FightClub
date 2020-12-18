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
				std::unique_ptr<characterstuff::Attributes> m_attributes;
				CharacterType m_characterType;

			public:
				Character(std::unique_ptr<characterstuff::Attributes> attributes, CharacterType characterType) :
					m_attributes{ std::move(attributes) },
					m_characterType{ characterType }
				{
				}

				Character(Character&& character) :
					m_attributes{ std::move(character.m_attributes) },
					m_characterType{ character.m_characterType }
				{
				}

				Character(std::unique_ptr<Character> character) :
					m_attributes{ std::move(character->m_attributes) },
					m_characterType{ character->m_characterType }
				{
				}

				virtual ~Character() {};

				characterstuff::Attributes* getAttributes() const { return m_attributes.get(); }
				virtual characterstuff::Equipment* getEquipment() const = 0;
				virtual const characterstuff::weapons::Weapon* const getWeapon() const = 0;
				CharacterType getCharcterType() const { return m_characterType; }

				void restoreHp() { m_attributes->setHp(100); }
			};
		}
	}
}