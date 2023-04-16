#pragma once

#include "BaseConnectionHandler.hpp"
#include "RequestProcesserContainer.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            class HttpConnectionHandler : public BaseConnectionHandler
            {
            public:
                HttpConnectionHandler(net::io_service& ios, const std::string& address, const std::string& port,
                                        const RequestProcesserContainer& requestProcesserContainer) :
                                        BaseConnectionHandler(ios, address, port),
                                        m_requestProcesserContainer(&requestProcesserContainer)
                {
                }

            private:
                void startConnection(tcp::socket&& socket) override;

            private:
                const RequestProcesserContainer* m_requestProcesserContainer;
            };

        }
    }
}