#pragma once

#include "BoostCommon.hpp"

namespace fightClub::core::network
{
    class HttpClient
    {
    public:
        void connectAsync(const std::string& host, const std::string& port);

    private:
        net::io_service m_ios;
        beast::tcp_stream m_stream;
    };
}