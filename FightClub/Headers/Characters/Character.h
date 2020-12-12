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
			std::unique_ptr<characterstuff::Equipment> m_equipment;
			std::unique_ptr<characterstuff::weapons::Weapon> m_weapon;
			CharacterType m_characterType;

		public:
			Character(std::unique_ptr<characterstuff::Attributes> attributes, std::unique_ptr<characterstuff::Equipment> equipment, 
				CharacterType characterType, std::unique_ptr<characterstuff::weapons::Weapon> weapon = {}) :
				m_attributes{ std::move(attributes) },
				m_equipment{ std::move(equipment) },
				m_weapon{ std::move(weapon) },
				m_characterType{ characterType }
			{
			}

			Character(Character&& character) :
				m_attributes{ std::move(character.m_attributes) },
				m_equipment{ std::move(character.m_equipment) },
				m_weapon{ std::move(character.m_weapon) },
				m_characterType{ character.m_characterType }
			{
			}

			Character(std::unique_ptr<Character> character) :
				m_attributes{ std::move(character->m_attributes) },
				m_equipment{ std::move(character->m_equipment) },
				m_weapon{ std::move(character->m_weapon) },
				m_characterType{ character->m_characterType }
			{
			}

			virtual ~Character() {};

			characterstuff::Attributes* getAttributes() const { return m_attributes.get(); }
			characterstuff::Equipment* getEquipment() const { return m_equipment.get(); }
			const characterstuff::weapons::Weapon* const getWeapon() { return m_weapon.get(); }
			//void setWeapon(Weapon* weapon) { m_weapon = std::make_unique<Weapon>(weapon); }
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

