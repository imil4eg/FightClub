#include "FighterBuilder.hpp"

#include <iostream>
#include <functional>

#include <boost/bind/bind.hpp>

#include "CharacterModel.hpp"
#include "IConfigReader.hpp"
#include "JsonAttributes.hpp"
#include "JsonDefinitions.hpp"
#include "ModelToJsonMapper.hpp"
#include "RequestHandlerPaths.hpp"
#include "ServiceUrls.hpp"

namespace FightClub::Server::Fight {

            FighterBuilder::FighterBuilder(FighterConnectionPtr connection, FighterReadyHandler handler, Common::IConfigReader& configReader, net::io_service& ios) :
                m_connection(connection),
                m_readyHandler(handler),
                m_configReader(&configReader),
                m_userId{-1}
            {
                std::string characterAPIUrl{m_configReader->get(ServiceUrls::CharacterAPIHost)->value};
                std::string characterAPIPort{m_configReader->get(ServiceUrls::CharacterAPIPort)->value};
                m_characterAPIClient = std::make_unique<Common::HttpClient>(ios, characterAPIUrl, characterAPIPort);
            }

            void FighterBuilder::startAsync()
            {
                json request;
                request.emplace_back(Common::RequestHandlerPaths::CharacterGetByUserId);
                
                m_connection->requestAsync(request.dump(), std::bind(&FighterBuilder::onUserIdReceived, shared_from_this(), std::placeholders::_1));
            }

            void FighterBuilder::onUserIdReceived(const std::string& response)
            {
                m_userId = std::stoi(response);

                m_characterAPIClient->connectAsync(std::bind(&FighterBuilder::onConnectedToCharaterAPI, shared_from_this(), std::placeholders::_1));
            }

            void FighterBuilder::onConnectedToCharaterAPI(bool success)
            {
                if (!success)
                {
                    std::cerr << "Couldn't connect to character API.";
                    return;
                }

                requestCharacter();
            }

            void FighterBuilder::requestCharacter()
            {
                json body;
                body[Common::JsonAttributes::userId] = m_userId;

                m_characterAPIClient->writeAsync(body, std::bind(&FighterBuilder::onCharacterReceived, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
            }

            void FighterBuilder::onCharacterReceived(const std::string& response, http::status status)
            {
                if (status != http::status::ok)
                {
                    std::cerr << "Request Character API error: " << response << '\n';
                    return;
                }

                json responseBody = json::parse(response);
                Common::CharacterModelPtr character = Common::JsonToCharacter(responseBody);

                auto fighter = std::make_shared<Fighter>(std::move(character), m_connection);

                if (m_connection->isDisconnected())
                    return;

                m_readyHandler(fighter);
            }
}