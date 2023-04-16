#pragma once

#include <functional>

#include <boost/beast/http/parser.hpp>

#include "BaseConnectionClient.hpp"

namespace FightClub::Network 
{
    class HttpClient : private ConnectionClient
    {
    public:
        using Ptr = std::unique_ptr<HttpClient>;
        using ResponseParserPtr = std::shared_ptr<http::response_parser<http::string_body>>;

    public:
        HttpClient(net::io_service& ios, const std::string& host, const std::string& port) :
            ConnectionClient(ios, host, port),
            stream_{ios},
            response_parser_{std::make_shared<http::response_parser<http::string_body>>()}
        {
        }

        ConnectionClient::ConnectTask ConnectAsync() {
            return ConnectionClient::ConnectAsync();
        }

        ReadTask SendRequest(RequestData&& request_data);

        void Close() {
            stream_.socket().shutdown(tcp::socket::shutdown_send);
        }

    protected:
        beast::tcp_stream& GetStream() override {
            return stream_;
        }

    private:
        beast::tcp_stream stream_;
        beast::flat_buffer buffer_;
        
        ResponseParserPtr response_parser_;
    };
}