#include "BaseConnectionHandler.hpp"

#include <iostream>

namespace FightClub {
    namespace Server {
        namespace Common {

            BaseConnectionHandler::BaseConnectionHandler(net::io_service& ios, const std::string& address, const std::string& port) : 
                m_ioService(ios),
                m_acceptor(net::make_strand(ios))
            {
                tcp::resolver resolver(ios);
                tcp::endpoint endpoint = *resolver.resolve(address, port).begin();
                m_acceptor.open(endpoint.protocol());
                m_acceptor.set_option(tcp::acceptor::reuse_address(true));
                m_acceptor.bind(endpoint);
                m_acceptor.listen();
            }

            BaseConnectionHandler::~BaseConnectionHandler() = default;

            void BaseConnectionHandler::run()
            {
                net::dispatch(m_acceptor.get_executor(), 
                              beast::bind_front_handler(&BaseConnectionHandler::beginAccept, shared_from_this()));  
            }

            void BaseConnectionHandler::beginAccept()
            {
                m_acceptor.async_accept(net::make_strand(m_ioService), 
                                        beast::bind_front_handler(&BaseConnectionHandler::onAccepted, shared_from_this()));
            }

            void BaseConnectionHandler::onAccepted(beast::error_code ec, tcp::socket socket)
            {
                if (ec)
                {
                    std::cerr << "accept error: " << ec.message() << '\n';
                }
                else
                {
                    startConnection(std::move(socket));
                }

                beginAccept();
            }
        }
    }
}