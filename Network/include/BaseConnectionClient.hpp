#pragma once

#include <coroutine>
#include <memory>

#include "RequestData.hpp"
#include "JsonDefinitions.hpp"

namespace FightClub::Network
{
    template <typename TResult>
    class NetworkTask {
    public:
        NetworkTask(TResult network_result) :
            result_{std::move(network_result)}
        {
        }

        TResult Get() const {
            return result_;
        }
            
        struct promise_type {
            TResult res; 

            auto get_return_object() noexcept {
                return NetworkTask<TResult>{ res };
            }

            std::suspend_never initial_suspend() {
                return {};
            }

            std::suspend_never final_suspend() noexcept {
                return {};
            }

            void return_value(TResult&& value) {
                res = std::move(value);
            }

            void unhandled_exception() {
                throw std::runtime_error("error during network process");
            }
        };

    private:
        TResult result_;
    };

    using TaskWithError = NetworkTask<beast::error_code>;
    using ReadTask = NetworkTask<std::pair<beast::error_code, std::string>>;

    class ConnectionClient {
    public:
        ConnectionClient(net::io_service& ios, std::string host, std::string port) :
            m_ios{ios},
            m_host(std::move(host)),
            m_port(std::move(port))
        {
        }

        virtual ~ConnectionClient() = default;

    protected:
        using ConnectTask = NetworkTask<std::pair<beast::error_code, tcp::resolver::results_type::endpoint_type>>; 
        ConnectTask ConnectAsync();

        const std::string& GetHost() const
        {
            return m_host;
        }

        virtual beast::tcp_stream& GetStream() = 0;

    private:
        net::io_service& m_ios;
        std::string m_host;
        std::string m_port;
    };
}