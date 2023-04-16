#pragma once

namespace FightClub {
    namespace Server {
        namespace Common {

            class Noncopyable
            {
            public:
                Noncopyable() = default;
                ~Noncopyable() = default;
                Noncopyable(const Noncopyable&) = delete;
                const Noncopyable& operator=(const Noncopyable&) = delete;
            };

        }
    }
}