#pragma once

#include "FighterConnection.hpp"

namespace FightClub {
    namespace Server {
        namespace Fight {

            class CharacterRequest
            {
            public:
                CharacterRequest(net::io_service& service, FighterConnectionPtr fighterConnection)
                {
                    tcp::socket socket()
                }
            };

        }
    }
}