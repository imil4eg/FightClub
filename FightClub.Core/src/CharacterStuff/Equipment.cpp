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
				Impl();

				int getArmorValue(const armors::Armor* armor) const
				{
					return armor == nullptr ? 0 : armor->getArmor();
				}

				~Impl();
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
					throw std::exception("Not implemented armor type");
				}
			}

			int Equipment::getArmorValue(battle::HitDirection hitDirection) const
			{
				const armors::Armor* armor;
				switch (hitDirection)
				{
				case battle::HitDirection::head:
					armor = this->getHelmet();
					break;
				case battle::HitDirection::body:
					armor = this->getCuirasse();
					break;
				case battle::HitDirection::legs:
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