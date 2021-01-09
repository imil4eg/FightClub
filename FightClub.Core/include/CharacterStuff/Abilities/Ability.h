#pragma once

#include <boost/uuid/uuid.hpp>
#include <string>
#include <memory>

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace abilities
			{
				class Ability
				{
				public:
					enum class Type
					{
						boost,
						attack,
						trap,
						max_type
					};

				private:
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					Ability(std::string name, Type type, int cost, int damage);
					Ability(boost::uuids::uuid&& id, std::string&& name, Type type, int cost, int damage);
					~Ability();

					const std::string& getName() const;
					const boost::uuids::uuid& getId() const;
				};
			}
		}
	}
}