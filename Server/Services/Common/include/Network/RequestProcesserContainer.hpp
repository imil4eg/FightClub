#pragma once

#include <string>
#include <functional>
#include <unordered_map>

#include "BoostCommon.hpp"
#include "Request.hpp"
#include "Noncopyable.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            using RequestProcesser_t = std::function<json(const json&)>;

            class RequestProcesserContainer : private Noncopyable
            {
            public:
                RequestProcesserContainer();
                ~RequestProcesserContainer();
                
                RequestProcesserContainer(const RequestProcesserContainer&&) = delete;

                void insert(const std::string& path, http::verb httpMethod, 
                                RequestProcesser_t handler);

                RequestProcesser_t get(const std::string& path, http::verb method) const;
                
            private:
                struct Impl;
                std::unique_ptr<Impl> pImpl;
            };
                           
        }
    }
}