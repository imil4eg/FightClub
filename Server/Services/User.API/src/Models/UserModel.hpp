#pragma once

#include <string>
#include <memory>

namespace FightClub {
    namespace Server {
        namespace User {

            struct UserModel
            {
                UserModel(int a_id, const std::string& a_userName, const std::string& a_password) : 
                    id{a_id},
                    userName{a_userName},
                    passwordHash{a_password}
                {
                }

                UserModel(const std::string& a_userName, const std::string& a_password) : 
                    UserModel(0, a_userName, a_password)
                {
                }

                UserModel(int a_id, std::string&& a_userName, std::string&& a_passwordHash) : 
                    id{a_id},
                    userName{std::move(a_userName)},
                    passwordHash{std::move(a_passwordHash)}
                {
                }

                UserModel() = default;

                int id;
                std::string userName;
                std::string passwordHash; 
            };
            
        }
    }
}