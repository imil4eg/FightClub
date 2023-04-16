#include "CharacterController.hpp"

#include "ConfigParams.hpp"
#include "RequestHandlerPaths.hpp"

#include "CreateCharacterCommandHandler.hpp"
#include "ModelToJsonMapper.hpp"
#include "UpdateCharacterCommandHandler.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            CharacterController::CharacterController(ICharacterQueries& characterQueries,
                                                    Common::Mediator& mediator,
                                                    Common::RequestProcesserContainer& requestProcessersContainer) : 
                m_characterQueries(&characterQueries),
                m_mediator(&mediator)
            {
                requestProcessersContainer.insert(Common::RequestHandlerPaths::CharacterGetByUserId, http::verb::get, [&](const json& req){ return getByUserId(req);});
                requestProcessersContainer.insert(Common::RequestHandlerPaths::CharacterCreate, http::verb::post, [&](const json& req){ return create(req);});
                requestProcessersContainer.insert(Common::RequestHandlerPaths::CharacterUpdate, http::verb::post, [&](const json& req) { return update(req);});
            }

            json CharacterController::create(const json& request)
            {
                if (!request.contains(jsonAttributes::userId))
                {
                    throw std::runtime_error("User ID not specified.");
                }

                if (!request.contains(jsonAttributes::characterType))
                {
                    throw std::runtime_error("Character type not specified.");
                }

                int userId = request[jsonAttributes::userId].get<int>();
                if (m_characterQueries->doesExist(userId))
                {
                    throw std::runtime_error("User already have character.");
                }

                CreateCharacterCommand command(userId, static_cast<Common::CharacterType>(request[jsonAttributes::characterType].get<int>()));
                m_mediator->send(command);

                return json();        
            }

            json CharacterController::getByUserId(const json& request)
            {
                if (!request.contains(jsonAttributes::userId))
                {
                    return Common::createErrorResponseTemplate("The user ID not specified.");
                }

                int userId{request[jsonAttributes::userId].get<int>()};
                Common::CharacterModelPtr character{m_characterQueries->getByUserId(userId)};

                if (character == nullptr)
                {
                    return Common::createErrorResponseTemplate("User with ID " + std::to_string(userId) + " doesn't exist");
                }

                return Common::CharacterToJson(*character.get());
            }

            json CharacterController::update(const json& request)
            {
                if (!request.contains(jsonAttributes::ID) ||
                    !request.contains(jsonAttributes::userId))
                {
                    return Common::createErrorResponseTemplate("ID or User ID not specified.");    
                }

                UpdateCharacterCommand command(request[jsonAttributes::ID].get<int>(), Common::getIdOrNull(request, jsonAttributes::headId),
                                                Common::getIdOrNull(request, jsonAttributes::cuirassId), Common::getIdOrNull(request, jsonAttributes::bootsId),
                                                Common::getIdOrNull(request, jsonAttributes::weaponId));

                m_mediator->send(command);

                return json();
            }
        }
    }
}