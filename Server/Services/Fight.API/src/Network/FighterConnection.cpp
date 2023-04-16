#include "FighterConnection.hpp"

#include <iostream>

#include "JsonDefinitions.hpp"

namespace FightClub {
    namespace Server {
        namespace Fight {

            void FighterConnection::start(AcceptedHandler acceptHandler)
            {
                m_acceptedHandler = acceptHandler;

                try
                {
                    m_webSocket.set_option(websocket::stream_base::decorator(
                        [](websocket::response_type& res)
                        {
                            res.set(http::field::server, std::string(BOOST_BEAST_VERSION_STRING) + " websocket-server-sync");
                        }
                    ));
                    
                    m_webSocket.async_accept(
                        beast::bind_front_handler(
                            &FighterConnection::acceptAsync,
                            shared_from_this()
                        )
                    );
                }
                catch(const beast::system_error& e)
                {
                    if (e.code() != websocket::error::closed)
                        std::cerr << "Error: " << e.code().message() << '\n';
                }
                catch (const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }

            void FighterConnection::requestAsync(const std::string& request, ReadHandler readHandler)
            {
                m_readHandler = readHandler;

                m_webSocket.async_write(net::buffer(request), beast::bind_front_handler(&FighterConnection::onWriteAsync, shared_from_this()));
            }

            void FighterConnection::acceptAsync(const beast::error_code& ec)
            {
                if (ec)
                {
                    std::cerr << "Error accept: " << ec.message() << '\n';
                    return;
                }

                m_acceptedHandler(shared_from_this());
            }

            void FighterConnection::onWriteAsync(const beast::error_code& ec, std::size_t bytesWritten)
            {
                boost::ignore_unused(bytesWritten);

                if (ec)
                {
                    std::cerr << "error write: " << ec.message() << '\n';
                    return;
                }

                m_webSocket.async_read(m_buffer, beast::bind_front_handler(&FighterConnection::onReadAsync, shared_from_this()));
            }

            void FighterConnection::onReadAsync(const beast::error_code& ec, std::size_t bytesTransfered)
            {
                boost::ignore_unused(bytesTransfered);

                std::cout << "Message received.\n";

                if (ec == http::error::end_of_stream || 
                    ec == net::error::eof)
                {
                    std::cout << "User disconnected.\n";
                    close();
                    return;
                }

                if (ec)
                {
                    std::cout << "read error: " << ec.message() << '\n';
                    return;
                }

                std::string message{beast::buffers_to_string(m_buffer.data())};

                m_readHandler(message);
                m_readHandler = nullptr;
            }

            void FighterConnection::close()
            {
                m_isDisconnected = true;
                m_webSocket.close(tcp::socket::shutdown_send);
            }
        }
    }
}