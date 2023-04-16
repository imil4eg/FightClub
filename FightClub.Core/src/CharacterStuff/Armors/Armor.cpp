#include "CharacterStuff/Armors/Armor.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			namespace armors
			{
				struct Armor::Impl 
				{
					boost::uuids::uuid m_id;
					std::string m_name;
					std::unique_ptr<characterstuff::Attributes> m_attributes;
					characterstuff::armors::ArmorType m_type{};
					int m_armor{};

					Impl(boost::uuids::uuid id, const std::string& name, characterstuff::armors::ArmorType type, int armor,
						std::unique_ptr<characterstuff::Attributes> attributes) : 
						m_id{ id },
						m_name{ name },
						m_attributes{ std::move(attributes) },
						m_type{ type },
						m_armor{ armor }
					{
					}

					Impl(const std::unique_ptr<Impl>& impl) : 
						m_id{std::move(impl->m_id)},
						m_name{std::move(impl->m_name)},
						m_attributes{std::move(impl->m_attributes)},
						m_type{impl->m_type},
						m_armor{impl->m_armor}
					{
					}

					~Impl() = default;
				};

				Armor::Armor(boost::uuids::uuid id, const std::string& name, characterstuff::armors::ArmorType type, int armor,
					std::unique_ptr<characterstuff::Attributes> attributes) :
					pImpl(std::make_unique<Impl>(id, name, type, armor, std::move(attributes)))
				{
				}

				Armor::Armor(const Armor& armor) : 
					pImpl{ std::make_unique<Impl>(std::move(armor.pImpl)) }
				{
				}

				Armor::Armor(Armor&& armor) noexcept :
					pImpl(std::make_unique<Impl>(std::move(armor.pImpl)))
				{
				}

				Armor::Armor(const std::unique_ptr<Armor>&& armor) :
					pImpl(std::make_unique<Impl>(std::move(armor->pImpl)))
				{
				}

				Armor::~Armor() = default;

				const boost::uuids::uuid Armor::getId() const { return pImpl->m_id; }
				const std::string& Armor::getName() const { return pImpl->m_name; }
				const characterstuff::Attributes* Armor::getAttributes() { return pImpl->m_attributes.get(); }
				characterstuff::armors::ArmorType Armor::getType() const { return pImpl->m_type; }
				int Armor::getArmor() const { return pImpl->m_armor; }

				std::ostream& operator<<(std::ostream& out, const Armor& armor)
				{
					out << armor.getName() + " defence: " + std::to_string(armor.getArmor());
				
					return out;
				}
			}
		}
	}
}