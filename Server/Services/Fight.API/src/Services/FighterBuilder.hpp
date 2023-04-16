#pragma once

#include <functional>

#include <boost/beast/http/parser.hpp>

#include "BoostCommon.hpp"
#include "Fighter.hpp"
#include "FighterConnection.hpp"
#include "HttpClient.hpp"

namespace FightClub::Server::Common {
    class IConfigReader;
}

namespace FightClub::Server::Fight {

            class FighterBuilder : public std::enable_shared_from_this<FighterBuilder>
            {
            public:
                using FighterReadyHandler = std::function<void(FighterPtr)>;

            public:
                FighterBuilder(FighterConnectionPtr connection, FighterReadyHandler handler, Common::IConfigReader& configReader, net::io_service& ios);

                void startAsync();

            private:
                void onConnectedToCharaterAPI(bool success);
                void onUserIdReceived(const std::string& response);
                void requestCharacter();
                void onCharacterReceived(const std::string& response, http::status status);

            private:
                FighterConnectionPtr m_connection;
                FighterReadyHandler m_readyHandler;

                Common::IConfigReader* m_configReader;

                std::unique_ptr<Common::HttpClient> m_characterAPIClient;

                int m_userId;
            };
}