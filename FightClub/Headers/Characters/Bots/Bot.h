#ifndef BOT_H
#define BOT_H

#include <memory>
#include <iostream>

#include "../../CharacterStuff/Attributes.h"
#include "../Character.h"
#include "../CharacterType.h"
#include "../../CharacterStuff/Equipment.h"
#include "../../CharacterStuff/Weapons/Weapon.h"

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

			public:
				Bot(std::unique_ptr<characterstuff::Attributes> attributes, std::unique_ptr<characterstuff::Equipment> equipment, 
					CharacterType characterType, std::unique_ptr<characterstuff::weapons::Weapon> weapon = {}) :
					Character{ std::move(attributes), std::move(equipment), characterType },
					m_weapon{ std::move(weapon) }
				{
				}

				Bot(Bot&& bot) :
					Character{ std::move(bot) },
					m_weapon{ std::move(bot.m_weapon) }
				{
				}

				void playTurn(Character& player) override;
				void hit(Character& enemy, battle::HitDirection hitDirection) override;
				const characterstuff::weapons::Weapon* const getWeapon() const override { return m_weapon.get(); }
			};
		}
	}
}

#endif // !BOT_H

