#ifndef CHARACTER_H
#define CHARACTER_H

#include "../CharacterStuff/Attributes.h"
#include "../CharacterStuff/Armors/Armor.h"
#include "CharacterType.h"
#include "../CharacterStuff/Equipment.h"
#include "../Battle/HitDirection.h"
#include "../CharacterStuff/Weapons/Weapon.h"

namespace fightclub
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
				m_attributes{std::move(character.m_attributes)},
				m_characterType{ character.m_characterType }
			{
			}

			Character(std::unique_ptr<Character> character) : 
				m_attributes{std::move(character->m_attributes)},
				m_characterType{ character->m_characterType }
			{
			}

			virtual ~Character() {};

			characterstuff::Attributes* getAttributes() const { return m_attributes.get(); }
			virtual characterstuff::Equipment* getEquipment() const = 0;
			virtual const characterstuff::weapons::Weapon* const getWeapon() const = 0;
			CharacterType getCharcterType() const { return m_characterType; }

			void restoreHp() { m_attributes->setHp(100); }
			void hit(Character& enemy, int damage)
			{
				enemy.getAttributes()->setHp(enemy.getAttributes()->getHp() - damage);
			}
			virtual void hit(Character& enemy, battle::HitDirection hitDirection) = 0;
			virtual void playTurn(Character& target) = 0;
		};
	}
}

#endif // !CHARACTER_H

