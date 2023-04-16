#include <nlohmann/json.hpp>

#include <jwt-cpp/jwt.h>

#include "ConfigParams.hpp"
#include "UserController.hpp"
#include "RequestHandlerPaths.hpp"
#include "NetworkExceptions.hpp"

namespace FightClub {
    namespace Server {
        namespace User {

            using JWT = Common::ConfigParams::JWT;

            struct UserController::Impl
            {
                Impl(IPasswordHasher& aPasswordHasher, IUserRepository& aRepository,
                    Common::IConfigReader& aConfigReader) :
                    passwordHasher(&aPasswordHasher),
                    repository(&aRepository),
                    configReader(&aConfigReader)
                {
                }

                IPasswordHasher* passwordHasher;
                IUserRepository* repository;
                Common::IConfigReader* configReader;
            };

            UserController::UserController(IPasswordHasher& passwordHasher, IUserRepository& repository, Common::IConfigReader& configReader, 
                                            Common::RequestProcesserContainer& requestProcessersContainer) :
                pImpl(std::make_unique<Impl>(passwordHasher, repository, configReader))
            {
                requestProcessersContainer.insert(Common::RequestHandlerPaths::UserLogin, http::verb::post, [&](const json& req){ return login(req);});
                requestProcessersContainer.insert(Common::RequestHandlerPaths::UserRegister, http::verb::post, [&](const json& req){ return registerUser(req);});
                requestProcessersContainer.insert(Common::RequestHandlerPaths::UserGetById, http::verb::get, [&](const json& req){ return getById(req);});
            }

            UserController::~UserController()
            {
            }

            json UserController::login(const json& request)
            { 
                if (!request.contains(jsonAttributes::userName) && 
                    !request[jsonAttributes::userName].is_string())
                {
                    throw Common::InvalidParameterException(jsonAttributes::userName);
                }

                std::string name{request[jsonAttributes::userName].get<std::string>()};

                auto user{pImpl->repository->findByName(name)};

                if (!request.contains(jsonAttributes::password) &&
                    !request[jsonAttributes::password].is_string())
                {
                    throw Common::InvalidParameterException(jsonAttributes::password);
                }

                std::string passwordHash{pImpl->passwordHasher->hash(request[jsonAttributes::password].get<std::string>())};

                if (user == nullptr || 
                    user->passwordHash != passwordHash) 
                {
                    throw Common::DataError("Incorrect login or password.");
                }

                json message;
                
                return message;
            }

            json UserController::registerUser(const json& request)
            {
                if (!request.contains(jsonAttributes::userName) &&
                    !request[jsonAttributes::userName].is_string())
                {
                    throw Common::InvalidParameterException(jsonAttributes::userName);
                }

                if (!request.contains(jsonAttributes::password) &&
                    !request[jsonAttributes::password])
                {
                    throw Common::InvalidParameterException(jsonAttributes::password);
                }

                auto user{pImpl->repository->findByName(request[jsonAttributes::userName].get<std::string>())};

                if (user != nullptr)
                {
                    throw Common::DataError("User with specified name already exist.");
                }

                std::string passwordHash{pImpl->passwordHasher->hash(request[jsonAttributes::password].get<std::string>())};
                UserModel model(request[jsonAttributes::userName].get<std::string>(), passwordHash);

                pImpl->repository->create(model);

                json response;

                return response;
            }
            
            json UserController::getById(const json& request)
            {
                if (!request.contains(jsonAttributes::userId) &&
                    !request[jsonAttributes::userId].is_number_integer())
                {
                    throw Common::InvalidParameterException(jsonAttributes::userId);
                }

                int userId{request[jsonAttributes::userId].get<int>()};

                UserEntityRef user{pImpl->repository->findById(userId)};

                json response;

                if (user == nullptr)
                {
                    response[jsonAttributes::message] = "User not found.";
                }
                else
                {
                    json userResponse;
                    userResponse.emplace(jsonAttributes::ID, user->id);
                    userResponse.emplace(jsonAttributes::password, user->passwordHash);
                    userResponse.emplace(jsonAttributes::userName, user->userName);

                    response[jsonAttributes::user] = userResponse;
                }

                return response;
            }

        }
    }
}