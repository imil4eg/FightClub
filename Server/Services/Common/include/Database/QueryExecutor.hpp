#pragma once

#include <memory>

#include "IConnectionFactory.hpp"
#include "IQueryExecutor.hpp"

namespace FightClub {
    namespace Server {
        namespace Common{

            class QueryExecutor : public IQueryExecutor
            {
            private:
                using ConnectionRef = std::unique_ptr<QString, std::function<void(QString*)>>;

            public:
                QueryExecutor(const IConnectionFactory& connectionFactory);

                ~QueryExecutor();

            private:
                virtual void executeImpl(const QString& query, QueryParamsValues values) const override;
                virtual QueryResult executeSingleResultImpl(const QString& query, QueryParamsValues values, QueryOutArgNames outArgsNames) const override;
                virtual QueryResultArray executeMultipleResultImpl(const QString& query, QueryParamsValues values, QueryOutArgNames outArgsNames) const override;

            private:
                struct Impl;
                std::unique_ptr<Impl> pImpl;
            };
        }
    }
}