#include "AbilityQueries.hpp"

#include "TableColumnsNames.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            Common::AbilityModelPtrArray AbilityQueries::getByCharacterIdImpl(int characterId) const
            {
                QString queryString{"SELECT Abilities.ID, Abilities.Name, Abilities.Cost, Abilities.Value, Abilities.Value, Abilities.Duration, Abilities.AbilityTypeID\n"
                                    "FROM Abilities\n"
                                    "INNER JOIN CharacterAbilities ON Abilities.ID = CharacterAbilities.AbilityID AND CharacterAbilities.CharacterID = ?"};
                Common::QueryResultArray results{m_queryExecutor->executeMultipleResult(queryString,
                {
                    characterId
                },
                {
                    TableColumnsNames::ID,
                    TableColumnsNames::Name,
                    TableColumnsNames::Cost,
                    TableColumnsNames::Value,
                    TableColumnsNames::Duration,
                    TableColumnsNames::AbilityTypeID
                })};

                Common::AbilityModelPtrArray abilities(results.size());

                if (results.empty())
                    return abilities;

                auto abilityIterator = abilities.begin();
                for (Common::QueryResult& queryResult : results)
                {
                    *abilityIterator = std::make_unique<Common::AbilityModel>(queryResult[TableColumnsNames::ID].toInt(),
                                                        queryResult[TableColumnsNames::Name].toString().toStdString(),
                                                        queryResult[TableColumnsNames::Cost].toInt(),
                                                        queryResult[TableColumnsNames::Value].toInt(),
                                                        queryResult[TableColumnsNames::Duration].toInt(),
                                                        static_cast<Common::AbilityModel::AbilityType>(queryResult[TableColumnsNames::AbilityTypeID].toInt()));
                    ++abilityIterator;
                }

                return abilities;
            }

        }
    }
}