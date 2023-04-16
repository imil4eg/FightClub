#include "InventoryQueries.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            Common::InventoryModelPtr InventoryQueries::getByCharacterIdImpl(int characterId) const
            {
                ArmorModelPtrArray armors = m_armorQueries->getCharacters(characterId);
                WeaponModelPtrArray weapons = m_weaponQueries->getCharacters(characterId);

                return std::make_unique<Common::InventoryModel>(armors.begin(), armors.end(), weapons.begin(), weapons.end());
            }

        }
    }
}