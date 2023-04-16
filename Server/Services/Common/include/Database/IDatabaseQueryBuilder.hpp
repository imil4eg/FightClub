#pragma once

#include <QtCore/QString>

namespace FightClub {
    namespace Server {
        namespace Common {

            using QueryParamsNames = std::initializer_list<QString>;

            class IDatabaseQueryBuilder
            {
            public:
                virtual ~IDatabaseQueryBuilder() = default;
                virtual QString buildSelectQuery() const = 0;
                virtual QString buildSelectQuery(QueryParamsNames params) const = 0;
                virtual QString buildSelectByIdQuery(QueryParamsNames params, const QString& idColumnName) const = 0;
                virtual QString buildInsertQuery(QueryParamsNames params) const = 0;
                virtual QString buildUpdateQueryWithoutCondition(QueryParamsNames params) const = 0;
                virtual QString buildUpdateById(QueryParamsNames params, const QString& idColumnName) const = 0;
                virtual QString buildDeleteQueryWithoutCondition() const = 0; 
                
            };

        }
    }
    
} // namespace Fightclub
