#pragma once

#include <memory>

#include "CharacterStuff/Equipment.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			class StaticEquipment : public Equipment
			{
			private:
				std::unique_ptr<armors::Armor> m_helmet;
				std::unique_ptr<armors::Armor> m_cuirass;
				std::unique_ptr<armors::Armor> m_boots;

			public:
				StaticEquipment(std::unique_ptr<armors::Armor> helmet = {}, std::unique_ptr<armors::Armor> cuirass = {},
					std::unique_ptr<armors::Armor> boots = {}) :
					m_helmet{ std::move(helmet) },
					m_cuirass{ std::move(cuirass) },
					m_boots{ std::move(boots) }
				{
				}

				const armors::Armor* getHelmet() const override { return m_helmet.get(); }
				const armors::Armor* getCuirasse() const override { return m_cuirass.get(); }
				const armors::Armor* getBoots() const override { return m_boots.get(); }
			};
		}
	}
}