#pragma once

#include <memory>
#include <QtCore/QVariant>

#include "IDatabaseQueryBuilder.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            class DatabaseQueryBuilder : public IDatabaseQueryBuilder
            {
            public:
                DatabaseQueryBuilder(const QString& tableName);
                DatabaseQueryBuilder(const std::string& tableName);
                ~DatabaseQueryBuilder();

                QString buildSelectQuery() const override;
                QString buildSelectQuery(QueryParamsNames params) const override;
                QString buildSelectByIdQuery(QueryParamsNames params, const QString& idColumnName) const override;
                QString buildInsertQuery(QueryParamsNames params) const override;
                QString buildUpdateQueryWithoutCondition(QueryParamsNames params) const override;
                QString buildUpdateById(QueryParamsNames params, const QString& idColumnName) const override;
                QString buildDeleteQueryWithoutCondition() const override;
            
            private:
                struct Impl;
                std::unique_ptr<Impl> pImpl;
            };

        }
    }
}