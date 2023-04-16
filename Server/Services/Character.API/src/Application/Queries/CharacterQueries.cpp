#include "CharacterQueries.hpp"

#include "TableColumnsNames.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            Common::CharacterModelPtr CharacterQueries::getByUserIdImpl(int userId) const
            {
                Common::QueryResult result{get(userId)};

                if (result.size() == 0)
                    return nullptr;

                int characterId = result[TableColumnsNames::ID].toInt();
                Common::InventoryModelPtr inventory = m_inventoryQueries->getByCharacterId(characterId);
                Common::AttributeModelPtr attribute = m_attributeQueries->get(characterId);

                Common::AbilityModelPtrArray abilities = m_abilityQueries->getByCharacterId(characterId);

                return  std::make_unique<Common::CharacterModel>(characterId, 
                                                        static_cast<Common::CharacterType>(result[TableColumnsNames::CharacterType].toInt()),
                                                        result[TableColumnsNames::UserID].toInt(),
                                                        std::move(attribute),
                                                        inventory->getArmorById(result[TableColumnsNames::HeadID].toInt()),
                                                        inventory->getArmorById(result[TableColumnsNames::CuirassID].toInt()),
                                                        inventory->getArmorById(result[TableColumnsNames::BootsID].toInt()),
                                                        inventory->getWeaponById(result[TableColumnsNames::WeaponID].toInt()),
                                                        std::move(abilities),
                                                        std::move(inventory));

            }

            bool CharacterQueries::doesExistImpl(int userId) const
            {
                Common::QueryResult result{get(userId)};

                return result.size() > 0;
            }

            Common::QueryResult CharacterQueries::get(int userId) const
            {
                QString queryString{"SELECT * FROM Characters WHERE UserID = ?"};
                
                return m_queryExecutor->executeSingleResult(queryString,
                {
                    userId
                },
                {
                    TableColumnsNames::ID,
                    TableColumnsNames::CharacterType,
                    TableColumnsNames::UserID,
                    TableColumnsNames::AttributeID,
                    TableColumnsNames::HeadID,
                    TableColumnsNames::CuirassID,
                    TableColumnsNames::BootsID,
                    TableColumnsNames::WeaponID
                });
            }
        }
    }
}