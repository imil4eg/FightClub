#include "Characters/Character.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			struct Character::Impl
			{
				std::unique_ptr<characterstuff::Attributes> m_attributes;
				std::unique_ptr<characterstuff::Equipment> m_equipment;
				std::unique_ptr< abilitiesCointainer_t> m_abilitiesCointainer;
				CharacterType m_characterType;

				Impl(std::unique_ptr<characterstuff::Attributes> attributes,
				     std::unique_ptr<characterstuff::Equipment> equipment,
					 std::unique_ptr<abilitiesCointainer_t> abilitiesContainer,
					 CharacterType characterType) : 
					m_attributes{ std::move(attributes) },
					m_equipment{std::move(equipment)},
					m_abilitiesCointainer{std::move(abilitiesContainer)},
					m_characterType{ characterType }
				{
				}

				Impl(Impl&& impl) : 
					m_attributes{ std::move(impl.m_attributes) },
					m_equipment{std::move(impl.m_equipment)},
					m_abilitiesCointainer{std::move(impl.m_abilitiesCointainer)},
					m_characterType{ impl.m_characterType }
				{
				}

				Impl(std::unique_ptr<Impl> impl) : 
					m_attributes{ std::move(impl->m_attributes) },
					m_equipment{std::move(impl->m_equipment)},
					m_abilitiesCointainer{std::move(impl->m_abilitiesCointainer)},
					m_characterType{ impl->m_characterType }
				{
				}

				~Impl() = default;
			};

			Character::Character(std::unique_ptr<characterstuff::Attributes> attributes, std::unique_ptr<characterstuff::Equipment> equipment,
							     std::unique_ptr<abilitiesCointainer_t> abilitiesContainer, CharacterType characterType) :
				pImpl(std::make_unique<Impl>(std::move(attributes), std::move(equipment), std::move(abilitiesContainer), characterType))
			{
			}

			Character::Character(Character&& character) noexcept :
				pImpl(std::move(character.pImpl))
			{
			}

			Character::Character(std::unique_ptr<Character> character) :
				pImpl(std::move(character->pImpl))
			{
			}

			Character::~Character() = default;

			characterstuff::Attributes* Character::getAttributes() const { return pImpl->m_attributes.get(); }
			void Character::updateAttributes(std::unique_ptr<characterstuff::Attributes> attributes) { pImpl->m_attributes = std::move(attributes); }
			characterstuff::Equipment& Character::getEquipment() const { return *pImpl->m_equipment.get(); }
			Character::abilitiesCointainer_t& Character::getAbilitiesContainer() const { return *pImpl->m_abilitiesCointainer; }
			CharacterType Character::getCharcterType() const { return pImpl->m_characterType; }
			void Character::restoreHp() { pImpl->m_attributes->setHp(100); }

			std::ostream& operator<<(std::ostream& out, const Character& character)
			{
				out << *character.getAttributes() << '\n' 
					<< "Type: " << character.getCharcterType() << '\n'
					<< "Total armor: " << character.getEquipment().getTotalArmor() << '\n';
			
				return out;
			}
		}
	}
}