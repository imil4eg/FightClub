#pragma once

#include <string>

namespace FightClub {
    namespace Server {
        namespace Common {
            namespace RequestHandlerPaths {
                
                static const std::string& UserLogin{"user/login"};
                static const std::string& UserRegister{"user/register"};
                static const std::string& UserCheckToken{"user/checkToken"};
                static const std::string& UserGetById{"user/getById"};

                static const std::string& CharacterGetByUserId{"character/getByUserId"};
                static const std::string& CharacterCreate{"character/create"};
                static const std::string& CharacterUpdate{"character/update"};
            
            }
        }
    }
}