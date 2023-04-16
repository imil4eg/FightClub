#include "HttpConnectionHandler.hpp"

#include <iostream>

#include "HttpConnection.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            void HttpConnectionHandler::startConnection(tcp::socket&& socket)
            {
                std::cout << "Connection received\n";
                std::make_shared<HttpConnection>(std::move(socket), *m_requestProcesserContainer)->start();
            }

        }
    }
}