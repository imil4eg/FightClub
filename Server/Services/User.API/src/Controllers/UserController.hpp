#pragma once

#include "BaseController.hpp"
#include "ControllerCommon.hpp"
#include "IConfigReader.hpp"
#include "IUserRepository.hpp"
#include "IPasswordHasher.hpp"
#include "JsonHelpers.hpp"

namespace FightClub {
    namespace Server { 
        namespace User {

            class UserController : public Common::BaseController
            {
            public:
                UserController(IPasswordHasher& passwordHasher, IUserRepository& repository, Common::IConfigReader& configReader, 
                                Common::RequestProcesserContainer& requestProcessersContainer);
                ~UserController();

                json login(const json& request);
                json registerUser(const json& request);
                json getById(const json& request);

            private:
                struct Impl;
                std::unique_ptr<Impl> pImpl;
            };

        }
    }
}