#include "BaseController.hpp"

#include "JsonConfigReader.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            struct BaseController::Impl
            {
                Impl()
                {
                    rabbitQueuesConfig = std::make_unique<JsonConfigReader>("RabbitQueues.json");
                }

                std::unique_ptr<JsonConfigReader> rabbitQueuesConfig;
            };

            BaseController::BaseController()
            {
            }

            BaseController::~BaseController()
            {
            }

            IConfigReader* BaseController::getRabbitConfig() const
            {
                return pImpl->rabbitQueuesConfig.get();   
            }

        }
    }
}