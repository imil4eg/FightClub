#include "DatabaseQueryBuilder.hpp"

#include "DatabaseQueryDictionary.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            struct DatabaseQueryBuilder::Impl
            {
                Impl(const QString& aTableName) :
                    tableName(aTableName)
                {
                }

                Impl(const std::string& aTableName) : 
                    tableName(aTableName.c_str())
                {
                }

                QString buildHoldersForQuery(int count)
                {
                    QString holders;
                    holders.reserve((count * (DatabaseQueryDictionary::ParamaterHolder.size() + DatabaseQueryDictionary::CommaAndSpace.size()))
                                    - DatabaseQueryDictionary::CommaAndSpace.size());
                    int current{1};
                    while (current <= count)
                    {
                        holders += DatabaseQueryDictionary::ParamaterHolder;

                        if (current < count)
                        {
                            holders += DatabaseQueryDictionary::CommaAndSpace;
                        }

                        --count;
                    }

                    return holders;
                }

                QString buildColumnsNamesForQuery(const QueryParamsNames& params)
                {
                    QString columnNames;

                    for (const QString& param : params)
                    {
                        columnNames += param + DatabaseQueryDictionary::CommaAndSpace;
                    }

                    columnNames.resize(columnNames.size() - DatabaseQueryDictionary::CommaAndSpace.size());
                
                    return columnNames;
                }

                QString tableName;
            };

            DatabaseQueryBuilder::DatabaseQueryBuilder(const QString& tableName) : 
                pImpl(std::make_unique<Impl>(tableName))
            {
            }

            DatabaseQueryBuilder::DatabaseQueryBuilder(const std::string& tableName) : 
                pImpl(std::make_unique<Impl>(tableName))
            {
            }

            DatabaseQueryBuilder::~DatabaseQueryBuilder() = default;

            QString DatabaseQueryBuilder::buildSelectQuery() const
            {
                QString query{buildSelectQuery({DatabaseQueryDictionary::SelectAllColumns})};

                return query;
            }

            QString DatabaseQueryBuilder::buildSelectQuery(QueryParamsNames params) const
            {
                QString query("SELECT " + pImpl->buildColumnsNamesForQuery(params) + " FROM " + pImpl->tableName);

                return query;               
            }

            QString DatabaseQueryBuilder::buildSelectByIdQuery(QueryParamsNames params, const QString& idColumnName) const
            {
                QString query(buildSelectQuery(params) + " WHERE " + idColumnName + " = " + pImpl->buildHoldersForQuery(1));

                return query;
            }

            QString DatabaseQueryBuilder::buildInsertQuery(QueryParamsNames params) const
            {
                QString query("INSERT INTO " + pImpl->tableName + " (" + pImpl->buildColumnsNamesForQuery(params) + ") VALUES (" +
                                pImpl->buildHoldersForQuery(params.size()) + ")");
    
                return query;  
            }

            QString DatabaseQueryBuilder::buildUpdateQueryWithoutCondition(QueryParamsNames params) const
            {
                QString query("UPDATE " + pImpl->tableName + " SET ");

                for (const QString& param : params)
                {
                    query += param + DatabaseQueryDictionary::SetNewParameterPattern; 
                }

                query.resize(query.size() - DatabaseQueryDictionary::CommaAndSpace.size());

                return query;
            }

            QString DatabaseQueryBuilder::buildDeleteQueryWithoutCondition() const
            {
                return "DELETE FROM " + pImpl->tableName;
            }

            QString DatabaseQueryBuilder::buildUpdateById(QueryParamsNames params, const QString& idColumnName) const
            {
                QString query("UPDATE " + pImpl->tableName + " SET ");

                for (const QString& param : params)
                {
                    query += param + DatabaseQueryDictionary::SetNewParameterPattern; 
                }

                query.resize(query.size() - DatabaseQueryDictionary::CommaAndSpace.size());

                query += " " + idColumnName + " = " + DatabaseQueryDictionary::ParamaterHolder;

                return query;
            }
        }
    }
}