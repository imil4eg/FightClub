#pragma once

#include "../JsonHelpers.hpp"
#include "../Noncopyable.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            class NetworkMessage : private Noncopyable 
            {
            public:
                NetworkMessage();
                NetworkMessage(const json& message);
                NetworkMessage(const json&& message);
                NetworkMessage(const std::string& handlerPath, const std::string& methodType);
                NetworkMessage(const NetworkMessage&& move);

                ~NetworkMessage();

                const json& operator[](const std::string& param) const;
                json& operator[](const std::string& param);

                const json& getMessage() const;
                
                template<typename T>
                T getValue(const std::string& param) const;

            private:
                struct Impl;
                std::unique_ptr<Impl> pImpl;
            };

        }
    }
}