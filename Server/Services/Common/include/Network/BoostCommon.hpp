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

namespace FightClub {
    namespace Server {
        namespace Common {
            namespace Network {

                typedef http::request<http::string_body> request_t;
                typedef http::response<http::string_body> response_t;

                using boostError_t = boost::system::error_code;
                using boostIOService_t = boost::asio::io_service;

                response_t buildResponse(const request_t& request, http::status status, const std::string& message);
            }
        }
    }
}