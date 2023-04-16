#include "WebsocketClient.hpp"

#include <iostream>
#include <string>

namespace FightClub::Network
{
    namespace {
        class ConnectAwaiter {
        public:
            ConnectAwaiter(WebsocketClient::websocket_stream& websocket, std::string host, 
                            tcp::resolver::results_type::endpoint_type endpoint_type) :
                websocket_(websocket),
                host_(std::move(host)),
                endpoint_type_(endpoint_type)
            {
            }

            bool await_ready() { return false; }
            void await_suspend(std::coroutine_handle<> coro) {
                websocket_.set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));

                websocket_.set_option(websocket::stream_base::decorator(
                [](websocket::request_type& req)
                {
                    req.set(http::field::user_agent,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-client-async");
                }));
        
                websocket_.async_handshake(host_ + ":" + std::to_string(endpoint_type_.port()), "/",
                [&coro, &ec_ = ec_](const beast::error_code& ec) {
                    ec_ = ec;
                    coro.resume();
                });
            }
            auto await_resume() {
                return ec_;
            }

        private:
            WebsocketClient::websocket_stream& websocket_;
            std::string host_;
            tcp::resolver::results_type::endpoint_type endpoint_type_;

            beast::error_code ec_;
        };

        class WriteAwaiter {
        public:
            WriteAwaiter(WebsocketClient::websocket_stream& websocket, RequestData&& request_data) :
                websocket_(websocket),
                request_data_(std::move(request_data))
            {
            }

            bool await_ready() { return false; }
            void await_suspend(std::coroutine_handle<> coro) {
                json request;
                request["ip"] = request_data_.IP;
                request["target"] = request_data_.target;
                request["method"] = request_data_.method;
                request["body"] = std::move(request_data_.body);
                websocket_.async_write(net::buffer(request.dump()), 
                [&coro, &ec_ = ec_](const beast::error_code& ec, std::size_t bytes_transfered) {
                    ec_ = ec;
                    coro.resume();
                });
            }
            auto await_resume() {
                return ec_;
            }

        private:
            WebsocketClient::websocket_stream& websocket_;
            RequestData request_data_;
            beast::error_code ec_;
        };

        class ReadAwaiter {
        public:
            ReadAwaiter(WebsocketClient::websocket_stream& websocket) :
                websocket_(websocket)
            {
            }

            bool await_ready() { return false; }
            void await_suspend(std::coroutine_handle<> coro) {
                websocket_.async_read(buffer_, [&coro, &ec_ = ec_](const beast::error_code& ec, std::size_t bytes_transfered) {
                    ec_ = ec;
                    coro.resume();
                });
            }
            auto await_resume() {
                return std::make_pair(ec_, beast::buffers_to_string(buffer_.data()));
            }

        private:
            WebsocketClient::websocket_stream& websocket_;

            beast::flat_buffer buffer_;
            beast::error_code ec_;
        };

        class CloseAwaiter {
        public:
            CloseAwaiter(WebsocketClient::websocket_stream& websocket) :
                websocket_(websocket)
            {
            }

            bool await_ready() { return false; }
            void await_suspend(std::coroutine_handle<> coro) {
                websocket_.async_close(websocket::close_code::normal, [&coro, &ec_ = ec_](const beast::error_code& ec) {
                    ec_ = ec;
                    coro.resume();
                });
            }
            auto await_resume() {
                return ec_;
            }

        private:
            WebsocketClient::websocket_stream& websocket_;
            beast::error_code ec_;
        };
    }

    TaskWithError WebsocketClient::ConnectAsync() {
        auto connect_task = ConnectionClient::ConnectAsync();
        const auto& [ec, endpoint_type] = connect_task.Get();

        if (ec) {
            throw std::runtime_error("could not connect: " + ec.message());
        }

        auto connect_result = co_await ConnectAwaiter{websocket_, GetHost(), endpoint_type};
        co_return connect_result;
    }

    TaskWithError WebsocketClient::WriteAsync(RequestData&& request_data) {
        auto write_result = co_await WriteAwaiter(websocket_, std::move(request_data));
        co_return write_result;
    }

    ReadTask WebsocketClient::ReadAsync() {
        auto read_result = co_await ReadAwaiter(websocket_);
        co_return read_result;
    }

    TaskWithError WebsocketClient::CloseAsync() {
        auto close_result =  co_await CloseAwaiter(websocket_);
        co_return close_result;
    }      
}