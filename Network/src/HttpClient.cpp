#include "HttpClient.hpp"

#include <iostream>

namespace FightClub::Network
{

    namespace {

        class WriteAwaiter {
        public:
            WriteAwaiter(beast::tcp_stream& stream, RequestData&& request_data) :
                stream_(stream),
                request_data_(std::move(request_data))
            {
            }

            bool await_ready() { return false; }
            void await_suspend(std::coroutine_handle<> coro) {
                sent_request_ = std::make_unique<HttpRequest>(request_data_.method, request_data_.target, BoostVersion);
                sent_request_->set(http::field::host, request_data_.IP);
                sent_request_->body() = std::move(request_data_.body);
                sent_request_->prepare_payload();

                http::async_write(stream_, *sent_request_.get(), [&coro = coro, &ec_ = ec_](const beast::error_code& ec, std::size_t bytesTransfered)
                {
                    ec_ = ec;
                    coro.resume();
                });
    
            }
            auto await_resume() { return ec_; }

        private:
            beast::tcp_stream& stream_;
            RequestData request_data_;
            std::unique_ptr<http::request<http::string_body>> sent_request_;

            beast::error_code ec_;
        };

        class ReadAwaiter {
        public:
            ReadAwaiter(beast::tcp_stream& stream, HttpClient::ResponseParserPtr response_parser) :
                stream_{stream},
                response_parser_{response_parser}
            {
            }

            bool await_ready() { return false; }

            void await_suspend(std::coroutine_handle<> coro) {
                http::async_read(stream_, buffer_, *response_parser_.get(), [&coro = coro, &ec_ = ec_](const beast::error_code& ec, std::size_t bytesTransfered)
                {
                    ec_ = ec;
                    coro.resume();
                });
            }

            auto await_resume() {
                if (ec_) {
                    return std::make_pair(ec_, std::string());
                } 

                auto response = response_parser_->release();
                return std::make_pair(ec_, response.body());
            }

        private:
            beast::tcp_stream& stream_;
            beast::flat_buffer buffer_;
            HttpClient::ResponseParserPtr response_parser_;
            beast::error_code ec_;
        };
    }

    ReadTask HttpClient::SendRequest(RequestData&& request_data) {
        const auto write_error = co_await WriteAwaiter{stream_, std::move(request_data)};

        if (write_error) {
            throw std::runtime_error("could not send request " + write_error.message());
        }

        auto read_result = co_await ReadAwaiter{stream_, response_parser_};
        co_return read_result;
    }
}