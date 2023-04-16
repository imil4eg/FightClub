#pragma once

#include <boost/core/noncopyable.hpp>

#include "BoostCommon.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            class BaseConnectionHandler : public std::enable_shared_from_this<BaseConnectionHandler>, private boost::noncopyable
            {
            public:
                using endpoint = net::ip::basic_endpoint<net::ip::tcp>;

            public:
                BaseConnectionHandler(net::io_service& ios, const std::string& address, const std::string& port); 

                virtual ~BaseConnectionHandler();

                void run();

            private:
                virtual void startConnection(tcp::socket&& socket) = 0;

                void beginAccept();
                void onAccepted(beast::error_code ec, tcp::socket socket);

            private:
                net::io_service& m_ioService;
                tcp::acceptor m_acceptor;
            };

        }
    }
}