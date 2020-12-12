#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <memory>

#include "Armors/Armor.h"
#include "../Battle/HitDirection.h"

namespace fightclub
{
	namespace characterstuff
	{
		class Equipment
		{
		private:
			std::unique_ptr<armors::Armor> m_head;
			std::unique_ptr<armors::Armor> m_body;
			std::unique_ptr<armors::Armor> m_legs;

		public:
			Equipment(std::unique_ptr<armors::Armor> head = {}, std::unique_ptr<armors::Armor> body = {}, std::unique_ptr<armors::Armor> legs = {}) :
				m_head{ std::move(head) },
				m_body{ std::move(body) },
				m_legs{ std::move(legs) }
			{
			}

			const armors::Armor* getHelment() const { return m_head.get(); }
			const armors::Armor* getCuirasse() const { return m_body.get(); }
			const armors::Armor* getBoots() const { return m_legs.get(); }
			int getArmorValue(battle::HitDirection hitDirection) const;
		};
	}
}

#endif // !EQUIPMENT_H

