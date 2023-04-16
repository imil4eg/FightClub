#pragma once

#include "NetworkMessage.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            class Request : public NetworkMessage
            {
            public:
                Request();
                Request(const json& message, const std::string& replyTo);
                Request(const json&& message, const std::string& replyTo);
                Request(const std::string& queueName, const std::string& replyTo, const std::string& handlerPath, const std::string& methodType);
                Request(const Request&& request); 

                ~Request();

                const std::string& getReplyTo() const;
                const std::string getQueueName() const;

            private:
                struct Impl;
                std::unique_ptr<Impl> pImpl;
            };

        }

        using request_t = Common::Request;
        using requestRef_t = std::shared_ptr<Common::Request>;
    }
}