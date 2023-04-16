#include "UserRepository.hpp"

#include <iostream>

#include <QtCore/QVariant>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>

#include "QueryParamHolder.hpp"
#include "TableColumnsName.hpp"

namespace FightClub {
    namespace Server {
        namespace User {

            void UserRepository::create(const UserModel& user) const
            {
                if (findByName(user.userName) != nullptr)
                {
                    throw std::runtime_error("User with login " + user.userName + " already exists");
                }

                QString query{"INSERT INTO Users (UserName, Password) VALUES (?, ?)"};

                m_queryExecutor->execute(query, 
                {
                    user.userName.c_str(),
                    user.passwordHash.c_str()
                });
            }

            UserEntityRef UserRepository::findByName(const std::string& name) const
            {
                return findBy(TableColumnsName::UserName, name.c_str());
            }

            UserEntityRef UserRepository::findById(int id) const
            {
                return findBy(TableColumnsName::ID, id);
            }

            UserEntityRef UserRepository::findBy(const QString& columnName, QVariant value) const
            {
                QString query{"SELECT * FROM Users WHERE " + columnName + " = ?"};
                
                Common::QueryResult result{m_queryExecutor->executeSingleResult(query,
                {
                    value    
                },
                {
                    TableColumnsName::ID,
                    TableColumnsName::UserName,
                    TableColumnsName::Password
                })};

                UserEntityRef entity{nullptr};
                if (result.size() < 1)
                    return entity;

                entity = std::make_unique<UserModel>(result[TableColumnsName::ID].toInt(), 
                                     result[TableColumnsName::UserName].toString().toStdString(),
                                     result[TableColumnsName::Password].toString().toStdString());
                return entity;
            }
        }
    }
}