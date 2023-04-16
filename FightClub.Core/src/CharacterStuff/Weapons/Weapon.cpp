#include "CharacterStuff/Weapons/Weapon.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace weapons
			{
				struct Weapon::Impl
				{
					boost::uuids::uuid m_id{};
					std::string m_name{};
					int m_damage{};

					Impl(boost::uuids::uuid& uuid, std::string& name, int damage) : 
						m_id{uuid},
						m_name{ name },
						m_damage{ damage }
					{
					}

					Impl(Impl& impl) : 
						m_id{impl.m_id},
						m_name{ impl.m_name },
						m_damage{ impl.m_damage }
					{
					}

					Impl(std::unique_ptr<Impl> impl) : 
						m_id{impl->m_id},
						m_name{ impl->m_name },
						m_damage{ impl->m_damage }
					{
					}

					Impl(Impl&& impl) : 
						m_id{std::move(impl.m_id)},
						m_name{ std::move(impl.m_name) },
						m_damage{ impl.m_damage }
					{
					}

					~Impl() = default;
				};

				Weapon::Weapon(boost::uuids::uuid& uuid, std::string& name, int damage) :
					pImpl{ std::make_unique<Impl>(uuid, name, damage) }
				{
				}

				Weapon::Weapon(Weapon& weapon) :
					pImpl{ std::make_unique<Impl>(std::move(weapon.pImpl)) }
				{
				}

				Weapon::Weapon(Weapon&& weapon) noexcept : 
					pImpl{std::make_unique<Impl>(std::move(weapon.pImpl))}
				{
				}

				Weapon::~Weapon() noexcept = default;

				int Weapon::getDamage() const { return pImpl->m_damage; }
				const std::string& Weapon::getName() const { return pImpl->m_name; }
				const boost::uuids::uuid& Weapon::getId() const { return pImpl->m_id; }
				
				std::ostream& operator<<(std::ostream& out, const Weapon& weapon)
				{
					out << "Name: " + weapon.getName() + " damage: " + std::to_string(weapon.getDamage());

					return out;
				}
			}
		}
	}
}