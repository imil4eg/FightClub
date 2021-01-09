#pragma once

#include "Characters/Character.h"
#include "CharacterStuff/StaticEquipment.h"
#include "CharacterStuff/Abilities/AbilitiesContainer.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			namespace bots
			{
				class Bot : public Character
				{
				private:
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					Bot(std::unique_ptr<characterstuff::Attributes> attributes, std::unique_ptr<characterstuff::StaticEquipment> equipment,
						std::unique_ptr<characterstuff::abilities::AbilitiesContainer> abilitiesContainer,
						CharacterType characterType, std::unique_ptr<characterstuff::weapons::Weapon> weapon = {});

					Bot(Bot&& bot) noexcept;

					~Bot();

					const characterstuff::weapons::Weapon* const getWeapon() const override;
				};
			}
		}
	}
}