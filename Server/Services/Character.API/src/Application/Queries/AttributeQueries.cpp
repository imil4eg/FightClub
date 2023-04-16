#include "AttributeQueries.hpp"

#include "TableColumnsNames.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            Common::AttributeModelPtr AttributeQueries::getImpl(int id) const
            {
                QString queryStirng{"SELECT * FROM Attributes WHERE ID = ?"};
                Common::QueryResult result{m_queryExecutor->executeSingleResult(queryStirng,
                {
                    id
                },
                {
                    TableColumnsNames::ID,
                    TableColumnsNames::Level,
                    TableColumnsNames::Strength,
                    TableColumnsNames::Agility
                })};

                if (result.empty())
                    return nullptr;

                return std::make_unique<Common::AttributeModel>(result[TableColumnsNames::ID].toInt(),
                                                            result[TableColumnsNames::Level].toInt(),
                                                            result[TableColumnsNames::Strength].toInt(),
                                                            result[TableColumnsNames::Agility].toInt());
            }

        }
    }
}