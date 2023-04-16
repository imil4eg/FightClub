#pragma once

#include "IPasswordHasher.hpp"

namespace FightClub {
    namespace Server {
        namespace User {

            class OpenSSLPasswordHasher : public IPasswordHasher
            {
            public:
                std::string hash(const std::string& value) const override;
            };

        }
    }
}