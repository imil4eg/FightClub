#pragma once

#include <boost/uuid/uuid.hpp>
#include <string>
#include <memory>
#include <iostream>

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace weapons
			{
				class Weapon
				{
				private:
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					Weapon(boost::uuids::uuid& uuid, std::string& name, int damage);

					Weapon(Weapon& weapon);

					Weapon(Weapon&& weapon) noexcept;

					virtual ~Weapon() noexcept;
					int getDamage() const;
					const std::string& getName() const;
					const boost::uuids::uuid& getId() const;
					
					friend std::ostream& operator<<(std::ostream& out, const Weapon& weapon);
				};
			}
		}
	}
}