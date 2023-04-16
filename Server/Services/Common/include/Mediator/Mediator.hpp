#pragma once

#include <typeindex>
#include <memory>
#include <unordered_map>

#include <boost/noncopyable.hpp>

#include "ICommandHandler.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            class Mediator : private boost::noncopyable
            {
            public:
                using CommandHandlerPtr = std::shared_ptr<ICommandHandler>;

            public:
                template<typename TKey>
                void registerHandler(CommandHandlerPtr handler)
                {
                    m_handlers.insert(std::make_pair(std::type_index(typeid(TKey)), handler));
                }

                template<typename TCommand>
                void send(TCommand& command)
                {
                    auto handlerIt = m_handlers.find(typeid(TCommand));
                    if (handlerIt == m_handlers.end())
                    {
                        throw std::logic_error("Unexpected command.");
                    }

                    handlerIt->second->handle(command);
                }

            private:
                std::unordered_map<std::type_index, CommandHandlerPtr> m_handlers;  
            };

        }
    }
}