#pragma once

#include <boost/uuid/uuid.hpp>
#include <string>
#include <memory>

#include "AbilityType.h"

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
				private:
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					Ability(std::string name, AbilityType type, int cost, int damage, int duration);
					Ability(boost::uuids::uuid&& id, std::string&& name, AbilityType type, int cost, int damage, int duration);
					~Ability();

					const std::string& getName() const;
					const boost::uuids::uuid& getId() const;
					AbilityType getType() const;
					int getCost() const;
					int getValue() const;
					int getDuration() const;
				};
			}
		}
	}
}