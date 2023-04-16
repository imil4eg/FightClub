#pragma once

#include <functional>

#include <boost/beast/http/parser.hpp>

#include "ConnectionClient.hpp"

namespace FightClub::Server::Common 
{
    class HttpClient : public ConnectionClient<HttpClient>
    {
    public:
        HttpClient(net::io_service& ios, const std::string& host, const std::string& port) :
            ConnectionClient(ios, host, port),
            m_stream{ios},
            m_requestParser{std::make_unique<http::request_parser<http::string_body>>()},
            m_responseParser{std::make_unique<http::response_parser<http::string_body>>()}
        {
        }

    private:
        void writeAsyncImpl(const json& body) override;
        void handleResolve(const beast::error_code& ec, tcp::resolver::results_type results) override;
        void closeImpl() override;

        void handleConnect(const beast::error_code& ec, tcp::resolver::results_type::endpoint_type);

        void onWriteFinisihed(const beast::error_code& ec, std::size_t bytesTransfered);
        void onReadAsync(const beast::error_code& ec, std::size_t bytesTransfered);

    private:
        beast::tcp_stream m_stream;
        beast::flat_buffer m_buffer;
        
        std::unique_ptr<http::request_parser<http::string_body>> m_requestParser;
        std::unique_ptr<http::response_parser<http::string_body>> m_responseParser;
        std::unique_ptr<http::request<http::string_body>> m_sentRequest;
        
        ConnectionReadyHandler m_connectionReadyHandler;
        ResponseHandler m_responseHandler;
    };
}