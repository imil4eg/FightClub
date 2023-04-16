#include "WebsocketClient.hpp"

namespace FightClub::Server::Common
{
    void WebsocketClient::handleResolve(const beast::error_code& ec, tcp::resolver::results_type results)
    {
        if (ec)
        {
            std::cerr << "Resolve failed. " << ec.message() << '\n';
            executeConnectionReadyHandler(false);
            clearConnectionReadyHandler();
            return;
        }

        beast::get_lowest_layer(m_websocket).async_connect(results, 
                                                        beast::bind_front_handler(&WebsocketClient::handleConnect, shared_from_this()));
    }

    void WebsocketClient::handleConnect(const beast::error_code& ec, tcp::resolver::results_type::endpoint_type ep)
    {
        if (ec)
        {
            std::cerr << "Connection failed. " << ec.message() << '\n';
            executeConnectionReadyHandler(false);
            clearConnectionReadyHandler();
            return; 
        }

        m_websocket.set_option(webSocket::stream_base::timeout::suggested(beast::role_type::client));

        m_websocket.set_option(websocket::stream::decorator(
            [](websocket::request_type& req)
            {
                req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-async");
            }));
        
        m_websocket.async_handshake(m_host + ":" + ep.port(), "/",
                    beast::bind_front_handler(&WebsocketClient::handleHandshake, shared_from_this());
    }

    void WebsocketClient::handleHandshake(const beast::error_code& ec)
    {
        if (ec)
        {
            std::cerr << "Connection failed. " << ec.message() << '\n';
            executeConnectionReadyHandler(false);
            clearConnectionReadyHandler();
            return;
        }

        executeConnectionReadyHandler(true);
        clearConnectionReadyHandler();
    }

    void WebsocketClient::writeAsyncImpl(const json& body)
    {
        m_websocket.async_write(net::buffer(body.dump()), beast::bind_front_handler(&WebsocketClient::handleWrite, shared_from_this()));
    }

    void WebsocketClient::handleWrite(const beast::error_code& ec, std::size_t bytesTransfered)
    {
        boost::ignore_unused(bytesTransfered);

        if (ec)
        {
            std::cerr << "Write error. " << ec.message() << '\n';
            executeResponseHandler(ec.message(), http::status::internal_server_error);
            clearResponseHandler();
            return;
        }

        m_websocket.async_read(m_buffer, beast::bind_front_handler(&WebsocketClient::handleRead, shared_from_this()));
    }

    void WebsocketClient::handleRead(const beast::error_code& ec, std::size_t bytesTransferred)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
        {
            std::cerr << "Read error. " << ec.message() << '\n';
            executeResponseHandler(ec.message(), http::status::internal_server_error);
            clearResponseHandler();
            return;
        }

        executeResponseHandler(beast::make_printable(m_buffer.data(), http::status::ok);
        clearResponseHandler();
    }

    void WebsocketClient::closeImpl()
    {
        m_websocket.async_close(websocket::close_code::normal,
            beast::bind_front_handler(
                &WebsocketClient::handleClose,
                shared_from_this()));
    }

    void WebsocketClient::handleClose(const beast::error_code& ec)
    {
        if (ec)
        {
            std::cerr << "Close error. " << ec.message() << '\n';
            return;
        }
    }
}