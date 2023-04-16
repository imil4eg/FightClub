#pragma once

#include <string>

namespace FightClub {
    namespace Server {
        namespace User {

            class IPasswordHasher
            {
            public:
                virtual ~IPasswordHasher() = default;

                virtual std::string hash(const std::string& value) const = 0;
            };

        }
    }
}