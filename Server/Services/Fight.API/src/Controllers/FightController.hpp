#pragma once

#include <boost/noncopyable.hpp>

#include "ControllerCommon.hpp"

namespace FightClub {
    namespace Server {
        namespace Fight {

            class FightController : private boost::noncopyable
            {
            public:
                FightController(Common::RequestProcesserContainer& requestProcessersContainer);

                json registerToSearch(const json& request);
            };

        }
    }
}