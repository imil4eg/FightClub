#include "BaseConnectionClient.hpp"

namespace FightClub::Network {

    namespace {

        class ResolveAwaiter {
        public:
            ResolveAwaiter(net::io_service& ios, const std::string& host, const std::string& port) :
                resolver_{ios},
                host_{host},
                port_{port}
            {
            }

            bool await_ready() { return false; }
            void await_suspend(std::coroutine_handle<> coro) {
                resolver_.async_resolve(host_, port_, 
                [&coro = coro,
                &ec_ = ec_,
                &resolver_result_ = resolver_result_]
                (const beast::error_code& ec,
                tcp::resolver::results_type results)
                {
                    ec_ = ec;
                    resolver_result_ = results;
                    coro.resume();
                });
            }
            auto await_resume() { return std::make_pair(ec_, resolver_result_); }

        private:
            const std::string& host_;
            const std::string& port_;
            tcp::resolver resolver_;

            tcp::resolver::results_type resolver_result_;
            beast::error_code ec_;
        };

        class ConnectAwaiter {
        public:
            ConnectAwaiter(beast::tcp_stream& stream, const tcp::resolver::results_type& resolver_result) :
                stream_(stream),
                resolver_result_(resolver_result)
            {
            }

            bool await_ready() { return false; }
            void await_suspend(std::coroutine_handle<> coro) {
                stream_.async_connect(resolver_result_, 
                [&ec_ = ec_, 
                &endpoint_type_ = endpoint_type_,
                &coro = coro]
                (const beast::error_code& ec,
                tcp::resolver::results_type::endpoint_type endpoint_type)
                {
                    ec_ = ec;
                    endpoint_type_ = endpoint_type;
                    coro.resume();
                });
            }
            auto await_resume() { return std::make_pair(ec_, endpoint_type_); }
    
        private:
            beast::tcp_stream& stream_;
            tcp::resolver::results_type resolver_result_;

            beast::error_code ec_;
            tcp::resolver::results_type::endpoint_type endpoint_type_;
        };
    }

    ConnectionClient::ConnectTask ConnectionClient::ConnectAsync() {
        const auto& [ec, results_type] = co_await ResolveAwaiter(m_ios, m_host, m_port);
            
        if (ec) {
            throw std::runtime_error("failed to resolve: " + ec.message());
        }

        auto connection_result = co_await ConnectAwaiter{GetStream(), results_type};
        co_return connection_result;
    }

}