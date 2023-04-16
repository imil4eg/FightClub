#include "Request.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            struct Request::Impl
            {
                Impl()
                {
                }

                Impl(const std::string& aReplyTo) : 
                    replyTo(aReplyTo)
                {
                }

                Impl(const std::string& aQueueName, const std::string& aReplyTo) :
                    replyTo(aReplyTo),
                    queueName(aQueueName)
                {
                }
 
                Impl(const std::unique_ptr<Impl>& impl) :
                    replyTo(std::move(impl->replyTo))
                {
                }

                std::string replyTo;
                std::string queueName;
            };

            Request::Request() :
                NetworkMessage(), 
                pImpl(std::make_unique<Impl>())
            {
            }

            Request::Request(const json& message, const std::string& replyTo) :
                NetworkMessage(message),
                pImpl(std::make_unique<Impl>(replyTo))
            {
            }

            Request::Request(const json&& message, const std::string& replyTo) : 
                NetworkMessage(std::move(message)),
                pImpl(std::make_unique<Impl>(replyTo))
            {
            }

            Request::Request(const std::string& queueName, const std::string& replyTo, const std::string& handlerPath, const std::string& methodType) :
                NetworkMessage(handlerPath, methodType),
                pImpl(std::make_unique<Impl>(queueName, replyTo))
            {
            }

            Request::Request(const Request&& request) :
                NetworkMessage(std::move(request)),
                pImpl(std::make_unique<Impl>(request.pImpl))
            {
            }

            Request::~Request() = default;

            const std::string& Request::getReplyTo() const
            {
                return pImpl->replyTo;
            }

            const std::string Request::getQueueName() const
            {
                return pImpl->queueName;
            }
        }
    }
}