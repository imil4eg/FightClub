#pragma once

#include <boost/noncopyable.hpp>

#include "IInventoryQueries.hpp"

#include "IArmorQueries.hpp"
#include "IWeaponQueries.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            class InventoryQueries : public IInventoryQueries, private boost::noncopyable
            {
            public:
                InventoryQueries(IArmorQueries& armorQueries, IWeaponQueries& weaponQueries) :
                    m_armorQueries(&armorQueries),
                    m_weaponQueries(&weaponQueries)
                {
                }

            private:
                Common::InventoryModelPtr getByCharacterIdImpl(int characterId) const override;

            private:
                IArmorQueries* m_armorQueries;
                IWeaponQueries* m_weaponQueries;
            };

        }
    }
}