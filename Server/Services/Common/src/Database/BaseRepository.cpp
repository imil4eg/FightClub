#include "QueryExecutor.hpp"

#include <iostream>

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

#include "DatabaseQueryBuilder.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            struct QueryExecutor::Impl
            {
                Impl(const IConnectionFactory& a_connectionFactory, const IDatabaseQueryBuilder& aQueryBuilder,
                     const QString& aTableName) : 
                    connectionFactory{&a_connectionFactory},
                    tableName{aTableName},
                    queryBuilder(&aQueryBuilder)
                {
                }

                void execute(QSqlQuery& query, QSqlDatabase& connection, const QString& queryStr, QueryParamsValues values)
                {
                    if (!connection.open())
                    {
                        throw std::runtime_error(connection.lastError().text().toStdString());
                    }

                    query.prepare(queryStr);

                    int valueIndex{0};
                    for (const QVariant& value : values)
                    {
                        query.bindValue(valueIndex, value);
                        ++valueIndex;
                    }

                    if (!query.exec())
                    {
                        throw std::runtime_error(query.lastError().text().toStdString());
                    }
                }

                void onError(const QString& connectionName, const std::exception& e)
                {
                    std::cerr << e.what() << '\n';

                    QSqlDatabase connection{QSqlDatabase::database(connectionName)};
                    connection.rollback();

                    throw e;
                }

                void cleanConnection(QString* connectionName)
                {
                    QSqlDatabase::removeDatabase(*connectionName);
                }

                const IConnectionFactory* connectionFactory;
                const QString tableName;
                const IDatabaseQueryBuilder* queryBuilder;
            };

            QueryExecutor::QueryExecutor(const IConnectionFactory& connectionFactory, const IDatabaseQueryBuilder& queryBuilder,
                                             const QString& databaseName) : 
                pImpl{std::make_unique<Impl>(connectionFactory, queryBuilder, databaseName)}
            {    
            }

            QueryExecutor::QueryExecutor(const IConnectionFactory& connectionFactory, const IDatabaseQueryBuilder& queryBuilder,
                                             const std::string& databaseName) : 
                QueryExecutor(connectionFactory, queryBuilder, QString(databaseName.c_str()))
            {
            }

            QueryExecutor::~QueryExecutor()
            {
            }

            void QueryExecutor::execute(const QString& queryStr, QueryParamsValues values) const
            {
                ConnectionRef connectionName(new QString(pImpl->connectionFactory->create()), [&](QString* name)
                {
                    pImpl->cleanConnection(name);
                });

                try
                {
                    QSqlDatabase connection{QSqlDatabase::database(*connectionName)};
                    QSqlQuery query(connection);

                    connection.transaction();
                    pImpl->execute(query, connection, queryStr, values);
                    connection.commit();
                }
                catch(const std::exception& e)
                {
                    pImpl->onError(*connectionName, e);
                }
            }

            QueryExecutor::QueryResult QueryExecutor::executeSingleResult(const QString& queryStr, QueryParamsValues values,
                                                                             QueryOutArgNames outArgsNames) const
            {
                ConnectionRef connectionName(new QString(pImpl->connectionFactory->create()), [&](QString* name)
                {
                    pImpl->cleanConnection(name);
                });

                QueryResult result;
                try
                {
                    QSqlDatabase connection{QSqlDatabase::database(*connectionName)};

                    QSqlQuery query(connection);

                    connection.transaction();
                    pImpl->execute(query, connection, queryStr, values);

                    if (query.next())
                    {
                        for (auto& outArgName : outArgsNames)
                        {
                            result[outArgName] = query.value(outArgName);
                        }
                    }

                    connection.commit();
                }
                catch(const std::exception& e)
                {
                    pImpl->onError(*connectionName, e);
                }

                return result;
            }

            QueryExecutor::QueryResultArray QueryExecutor::executeMultipleResult(const QString& queryStr, QueryParamsValues values,
                                                                                     QueryOutArgNames outArgsNames) const
            {
                ConnectionRef connectionName(new QString(pImpl->connectionFactory->create()), [&](QString* name)
                {
                    pImpl->cleanConnection(name);
                });

                QueryResultArray result;
                try
                {
                    QSqlDatabase connection{QSqlDatabase::database(*connectionName)};

                    QSqlQuery query(connection);

                    connection.transaction();
                    pImpl->execute(query, connection, queryStr, values);

                    while (query.next())
                    {
                        QueryResult current;

                        for (auto& outArgName : outArgsNames)
                        {
                            current[outArgName] = query.value(outArgName);
                        }

                        result.push_back(current);
                    }

                    connection.commit();
                }
                catch (const std::exception& e)
                {
                    pImpl->onError(*connectionName, e);
                }

                return result;
            }

            const IDatabaseQueryBuilder* const QueryExecutor::getQueryBuilder() const
            {
                return pImpl->queryBuilder;
            }
        }
    }
}