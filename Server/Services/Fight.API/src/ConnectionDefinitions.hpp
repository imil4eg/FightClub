#pragma once

#include <memory>

#include "FighterConnection.hpp"

namespace FightClub {
    namespace Server {
        namespace Fight {

            using FighterConnectionPtr = std::shared_ptr<FighterConnection>; 

        }
    }
}