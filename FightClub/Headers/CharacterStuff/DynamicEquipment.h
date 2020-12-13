#pragma once

#include "Equipment.h"

namespace fightclub
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
				m_helmet{helmet},
				m_cuirass{ cuirass },
				m_boots{ boots }
			{
			}

			const armors::Armor* getHelmet() const override { return m_helmet; }
			const armors::Armor* getCuirasse() const override { return m_cuirass; }
			const armors::Armor* getBoots() const override { return m_boots; }
		};
	}
}