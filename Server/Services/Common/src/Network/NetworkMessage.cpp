#include "NetworkMessage.hpp"

#include "JsonAttributes.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            struct NetworkMessage::Impl
            {
                Impl() :
                    message()
                {
                }

                Impl(const json& aMessage) :
                    message(aMessage)
                {
                }

                Impl(const json&& aMessage) :
                    message(std::move(aMessage))
                {
                }

                Impl(const Impl&& copy) : 
                    message(std::move(copy.message))
                {
                }

                json message;
            };

            NetworkMessage::NetworkMessage() :
                pImpl(std::make_unique<Impl>())
            {
            }

            NetworkMessage::NetworkMessage(const json& message) :
                pImpl(std::make_unique<Impl>(message))
            {
            }

            NetworkMessage::NetworkMessage(const json&& message) :
                pImpl(std::make_unique<Impl>(std::move(message)))
            {
            }

            NetworkMessage::NetworkMessage(const std::string& handlerPath, const std::string& methodType) : 
                pImpl(std::make_unique<Impl>())
            {
                pImpl->message[JsonAttributes::path] = handlerPath;
                pImpl->message[JsonAttributes::type] = methodType;
            }

            NetworkMessage::NetworkMessage(const NetworkMessage&& copy) : 
                pImpl(std::move(copy.pImpl.get()))
            {
            }

            NetworkMessage::~NetworkMessage() = default;

            const json& NetworkMessage::operator[](const std::string& param) const
            {
                return pImpl->message[param];
            }

            json& NetworkMessage::operator[](const std::string& param)
            {
                return pImpl->message[param];
            }

            const json& NetworkMessage::getMessage() const
            {
                return pImpl->message;
            }

            template<>
            int NetworkMessage::getValue(const std::string& param) const
            {
                return pImpl->message[param].get<int>();
            }

            template<>
            std::string NetworkMessage::getValue(const std::string& param) const
            {
                return pImpl->message[param].get<std::string>();
            }
        }
    }
}