#include "HttpStatuses.hpp"

namespace FightClub {
    namespace Server {
        namespace Common { 

            const int HttpStatus::ok = 200;
            const int HttpStatus::badRequest = 400;
            const int HttpStatus::unathorized = 401;

        }
    }
}