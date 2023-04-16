#include "WeaponQueries.hpp"

#include "TableColumnsNames.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            WeaponModelPtrArray WeaponQueries::getCharactersImpl(int characterId) const
            {
                QString queryString{"SELECT Weapons.ID, Weapons.Name, Weapons.Damage\n"
                                    "FROM Weapons\n"
                                    "INNER JOIN CharacterWeapons ON Weapons.ID = CharacterWeapons.WeaponID  AND CharacterWeapons.CharacterID = ?"};
                Common::QueryResultArray result{m_queryExecutor->executeMultipleResult(queryString, 
                {
                    characterId
                },
                {
                    TableColumnsNames::ID,
                    TableColumnsNames::Name,
                    TableColumnsNames::Damage
                })};

                WeaponModelPtrArray weapons;

                if (result.size() == 0)
                    return weapons;

                for (auto& queryResult : result)
                {
                    weapons.push_back(std::make_unique<Common::WeaponModel>(queryResult[TableColumnsNames::ID].toInt(),
                                                        queryResult[TableColumnsNames::Name].toString().toStdString(),
                                                        queryResult[TableColumnsNames::Damage].toInt()));
                }

                return weapons;
            }

        }
    }
}