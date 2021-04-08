#pragma once

#include <memory>
#include <iostream>

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			class Attributes
			{
			private:
				struct Impl;
				std::unique_ptr<Impl> pImpl;

			public:
				Attributes(int hp, int level, int damage, int strength, int agility, int stamina);
				~Attributes();

				int getHp() const;
				void setHp(int hp);
				int getDamage() const;
				int getLevel() const;
				int getStrength() const;
				int getAgility() const;
				int getStamina() const;

				friend std::ostream& operator<<(std::ostream& out, const Attributes& attributes);
			};
		}
	}
}
