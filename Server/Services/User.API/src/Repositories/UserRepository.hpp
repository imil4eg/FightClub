#pragma once

#include <memory>
#include <vector>

#include "IQueryExecutor.hpp"
#include "TableColumnsName.hpp"
#include "IUserRepository.hpp"

namespace FightClub {
    namespace Server {
        namespace User {

            class UserRepository : public IUserRepository
            {
            public:
                explicit UserRepository(Common::IQueryExecutor& queryExeuctor) : 
                    m_queryExecutor(&queryExeuctor)
                {
                }

                void create(const UserModel& user) const override; 
                UserEntityRef findByName(const std::string& name) const override;
                UserEntityRef findById(int id) const override; 

            private:
                UserEntityRef findBy(const QString& columnName, QVariant value) const;

            private:
                Common::IQueryExecutor* m_queryExecutor;
            };

        }

    }
}