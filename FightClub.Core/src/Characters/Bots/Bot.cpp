#include "Characters/Bots/Bot.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			namespace bots
			{
				struct Bot::Impl
				{
					std::unique_ptr<characterstuff::weapons::Weapon> m_weapon;
					
					Impl(std::unique_ptr<characterstuff::StaticEquipment> equipment, std::unique_ptr<characterstuff::weapons::Weapon> weapon) : 
						m_weapon{ std::move(weapon) }
					{
					}

					Impl(Impl&& impl) : 
						m_weapon{ std::move(impl.m_weapon) }
					{
					}
				};

				Bot::Bot(std::unique_ptr<characterstuff::Attributes> attributes, std::unique_ptr<characterstuff::StaticEquipment> equipment,
					std::unique_ptr<characterstuff::abilities::AbilitiesContainer> abilitiesContainer,
					CharacterType characterType, std::unique_ptr<characterstuff::weapons::Weapon> weapon) : 
					Character{ std::move(attributes), std::move(equipment), std::move(abilitiesContainer), characterType },
					pImpl{ std::make_unique<Impl>(std::move(equipment), std::move(weapon)) }
				{
				}

				Bot::Bot(Bot&& bot) noexcept : 
					Character{ std::move(bot) },
					pImpl{ std::move(bot.pImpl) }
				{
				}

				Bot::~Bot() = default;

				const characterstuff::weapons::Weapon* const Bot::getWeapon() const { return pImpl->m_weapon.get(); }
			}
		}
	}
}