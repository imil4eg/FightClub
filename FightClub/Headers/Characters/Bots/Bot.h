#ifndef BOT_H
#define BOT_H

#include <memory>
#include <iostream>

#include "Characters/Character.h"
#include "CharacterStuff/StaticEquipment.h"

namespace fightclub
{
	namespace characters
	{
		namespace bots
		{
			class Bot : public Character
			{
			private:
				std::unique_ptr<characterstuff::weapons::Weapon> m_weapon;
				std::unique_ptr<characterstuff::StaticEquipment> m_equipment;

			public:
				Bot(std::unique_ptr<characterstuff::Attributes> attributes, std::unique_ptr<characterstuff::StaticEquipment> equipment, 
					CharacterType characterType, std::unique_ptr<characterstuff::weapons::Weapon> weapon = {}) :
					Character{ std::move(attributes), characterType },
					m_equipment{ std::move(equipment) },
					m_weapon{ std::move(weapon) }
				{
				}

				Bot(Bot&& bot) noexcept :
					Character{ std::move(bot) },
					m_equipment{std::move(bot.m_equipment)},
					m_weapon{ std::move(bot.m_weapon) }
				{
				}

				void playTurn(Character& player) override;
				void hit(Character& enemy, battle::HitDirection hitDirection) override;
				const characterstuff::weapons::Weapon* const getWeapon() const override { return m_weapon.get(); }
				characterstuff::Equipment* getEquipment() const { return m_equipment.get(); }
			};
		}
	}
}

#endif // !BOT_H

