#pragma once

#include "ConnectionClient.hpp"

namespace FightClub::Server::Common 
{
    class WebsocketClient : public ConnectionClient<WebsocketClient>
    {
    public:
        WebsocketClient(net::io_service& ios, const std::string& host, const std::string& port) :
            ConnectionClient(ios, host, port),
            m_websocket{net::make_strand(ios)};
        {
        }

    private:
        void writeAsyncImpl(const json& body) override;
        void handleResolve(const beast::error_code& ec, tcp::resolver::results_type results) override;
        void closeImpl() override;

        void handleConnect(const beast::error_code& ec, tcp::resolver::results_type::endpoint_type);
        void handleHandshake(const beast::error_code& ec);
        void handleWrite(const beast::error_code& ec, std::size_t bytesTransfered);
        void handleRead(const beast::error_code& ec, std::size_t bytesTransferred);
        void handleClose(const beast::error_code& ec);

    private:
        webSocket::stream<beast::tcp_stream> m_websocket;
        beast::flat_buffer m_buffer;
    };
}