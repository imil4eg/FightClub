#pragma once

#include "UserModel.hpp"

namespace FightClub {
    namespace Server {
        namespace User {

            using UserEntityRef = std::unique_ptr<UserModel>;

            class IUserRepository
            {                
            public:
                virtual ~IUserRepository() = default;
                virtual void create(const UserModel& user) const = 0;
                virtual UserEntityRef findByName(const std::string& name) const = 0;
                virtual UserEntityRef findById(int id) const = 0;
            };
        }

    }
}