#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/http.hpp>

namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
using tcp = net::ip::tcp;

using HttpRequest = http::request<http::string_body>;
using HttpRequestPtr = std::unique_ptr<HttpRequest>;
using HttpRequestParser = http::request_parser<http::string_body>;
using HttpRequestParserPtr = std::unique_ptr<HttpRequestParser>;

static constexpr int BoostVersion = 10; 

namespace FightClub::Network {

    typedef http::request<http::string_body> request_t;
    typedef http::response<http::string_body> response_t;

    using boostError_t = boost::system::error_code;
    using boostIOService_t = boost::asio::io_service;

}