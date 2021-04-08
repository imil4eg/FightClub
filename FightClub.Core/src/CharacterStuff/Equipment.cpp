#include <memory>

#include "CharacterStuff/Equipment.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			struct Equipment::Impl
			{
				Impl() = default;

				int getArmorValue(const armors::Armor* armor) const
				{
					return armor == nullptr ? 0 : armor->getArmor();
				}

				~Impl() = default;
			};

			Equipment::Equipment() :
				pImpl{ std::make_unique<Impl>() }
			{
			}

			Equipment::~Equipment() = default;

			const armors::Armor* Equipment::getArmor(armors::ArmorType armorType) const
			{
				switch (armorType)
				{
				case characterstuff::armors::ArmorType::head:
					return this->getHelmet();
				case characterstuff::armors::ArmorType::body:
					return this->getCuirasse();
				case characterstuff::armors::ArmorType::legs:
					return this->getBoots();
				default:
					throw std::runtime_error("Not implemented armor type");
				}
			}

			int Equipment::getArmorValue(characterstuff::BodyPart hitDirection) const
			{
				const armors::Armor* armor;
				switch (hitDirection)
				{
				case characterstuff::BodyPart::head:
					armor = this->getHelmet();
					break;
				case characterstuff::BodyPart::body:
					armor = this->getCuirasse();
					break;
				case characterstuff::BodyPart::legs:
					armor = this->getBoots();
					break;
				default:
					throw std::out_of_range("Hit directory not implemented.");
				}

				if (armor == nullptr)
				{
					return 0;
				}
				else
				{
					return armor->getArmor();
				}
			}

			int Equipment::getTotalArmor() const
			{
				return pImpl->getArmorValue(this->getHelmet()) + pImpl->getArmorValue(this->getCuirasse()) + pImpl->getArmorValue(this->getBoots());
			}
		}
	}
}