#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/websocket.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

namespace websocket = beast::websocket;

int main(int argc, char** argv)
{
    const std::string host(argv[1]);
    const std::string port(argv[2]);
    const std::string target(argv[3]);
    int version = argc == 5 && !std::strcmp("1.0", argv[4]) ? 10 : 11;

    net::io_context ioc;

    tcp::resolver resolver{ioc};
    auto const results = resolver.resolve(host, port);

    websocket::stream<tcp::socket> webSocket{ioc};
    net::connect(webSocket.next_layer(), results);


    webSocket.set_option(websocket::stream_base::decorator(
        [](auto& req)
        {
            req.set(http::field::user_agent, std::string(BOOST_BEAST_VERSION_STRING) + " websocket-client-coro");
        }
    ));

    webSocket.handshake(host, "/");

    beast::flat_buffer buffer;
    webSocket.read(buffer);

    std::cout << beast::make_printable(buffer.data()) << '\n';

    webSocket.write(net::buffer(std::string("1")));

    //beast::tcp_stream stream(ioc);
    //stream.connect(results);

    //http::request<http::string_body> req{http::verb::get, "character/getByUserId", version};
    //req.set(http::field::host, host);
    //req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    //nlohmann::json body;
    //body["userId"] = 1;
    //req.body() = body.dump();
    //req.prepare_payload();
//
    //http::write(stream, req);
//
    //beast::flat_buffer buffer;
    //http::response<http::string_body> res;
    //http::read(stream, buffer, res);
//
    //std::cout << "Status: " << res.result() << '\n';
    //std::cout << "Body: " << res.body() << '\n';
}

