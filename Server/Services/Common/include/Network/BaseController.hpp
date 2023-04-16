#pragma once

#include <memory>

#include "IConfigReader.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            class BaseController
            {
            public:
                BaseController();
                ~BaseController();

            protected:
                IConfigReader* getRabbitConfig() const;

            private:
                struct Impl;
                std::unique_ptr<Impl> pImpl;
            };

        }
    }
}