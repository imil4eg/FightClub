#pragma once

#include <QtCore/QVariant>
#include <QtCore/QHash>

namespace FightClub {
    namespace Server {
        namespace Common {

            using QueryResult = QHash<QString, QVariant>;
            using QueryResultArray = std::vector<QueryResult>;
            using QueryParam = std::pair<QString, QVariant>;
            using QueryParamsNames = std::initializer_list<QString>;
            using QueryParamsValues = std::initializer_list<QVariant>;
            using QueryOutArgNames = std::initializer_list<QString>;

            class IQueryExecutor
            {
            public:
                inline void execute(const QString& query, QueryParamsValues values) const
                {
                    executeImpl(query, values);
                }

                inline QueryResult executeSingleResult(const QString& query, QueryParamsValues values, QueryOutArgNames outArgsNames) const
                {
                    return executeSingleResultImpl(query, values, outArgsNames);
                }
                
                inline QueryResultArray executeMultipleResult(const QString& query, QueryParamsValues values, QueryOutArgNames outArgsNames) const
                {
                    return executeMultipleResultImpl(query, values, outArgsNames);
                }

            public:
                virtual ~IQueryExecutor() = default;

            private:
                virtual void executeImpl(const QString& query, QueryParamsValues values) const = 0;
                virtual QueryResult executeSingleResultImpl(const QString& query, QueryParamsValues values, QueryOutArgNames outArgsNames) const = 0;
                virtual QueryResultArray executeMultipleResultImpl(const QString& query, QueryParamsValues values, QueryOutArgNames outArgsNames) const = 0;
            };

        }
    }
}