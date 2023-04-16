#pragma once

namespace FightClub {
    namespace Server { 
        namespace Common { 

            class HttpStatus
            {
            public:
                static const int ok;
                static const int badRequest;
                static const int unathorized;

                HttpStatus() = delete;
                ~HttpStatus() = delete;
            };

        }
    }
}