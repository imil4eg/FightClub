#pragma once

#include "CharacterStuff/Equipment.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			class DynamicEquipment : public Equipment
			{
			private:
				const armors::Armor* m_helmet;
				const armors::Armor* m_cuirass;
				const armors::Armor* m_boots;

			public:
				DynamicEquipment(const armors::Armor* helmet = nullptr, const armors::Armor* cuirass = nullptr, const armors::Armor* boots = nullptr) :
					m_helmet{ helmet },
					m_cuirass{ cuirass },
					m_boots{ boots }
				{
				}

				const armors::Armor* getHelmet() const override { return m_helmet; }
				const armors::Armor* getCuirasse() const override { return m_cuirass; }
				const armors::Armor* getBoots() const override { return m_boots; }
				void changeArmor(const armors::Armor* armor, armors::ArmorType armorType)
				{
					switch (armorType)
					{
					case armors::ArmorType::head:
						m_helmet = armor;
						break;
					case armors::ArmorType::body:
						m_cuirass = armor;
						break;
					case armors::ArmorType::legs:
						m_boots = armor;
						break;
					default:
						throw std::runtime_error("Specified armor type not implemented.");
					}
				}
			};
		}
	}
}