#include "ArmorQueries.hpp"

#include "ArmorType.hpp"
#include "TableColumnsNames.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            ArmorModelPtrArray ArmorQueries::getCharactersImpl(int characterId) const
            {
                QString queryString{"SELECT Armors.ID, Armors.AttributeID, Armors.ArmorTypeID, Armors.Name, Armors.Armor\n"
                                    "FROM Armors\n"  
                                    "INNER JOIN CharacterArmors ON Armors.ID = CharacterArmors.ArmorID AND CharacterArmors.CharacterID = ?"};

                Common::QueryResultArray result{m_queryExecutor->executeMultipleResult(queryString,
                {
                    characterId
                },
                {
                    TableColumnsNames::ID,
                    TableColumnsNames::AttributeID,
                    TableColumnsNames::ArmorType,
                    TableColumnsNames::Name,
                    TableColumnsNames::Armor
                })};

                ArmorModelPtrArray armors;

                if (result.empty())
                    return armors;

                for (auto& queryResult : result)
                {
                    Common::AttributeModelPtr attributeModel = m_attributeQueries->get(queryResult[TableColumnsNames::AttributeID].toInt());

                    armors.push_back(std::make_unique<Common::ArmorModel>(queryResult[TableColumnsNames::ID].toInt(),
                                                                std::move(attributeModel),
                                                                static_cast<Common::ArmorModel::ArmorType>(queryResult[TableColumnsNames::ArmorType].toInt()),
                                                                queryResult[TableColumnsNames::Name].toString().toStdString(),
                                                                queryResult[TableColumnsNames::Armor].toInt()));
                }

                return armors;
            }

        }
    }
}