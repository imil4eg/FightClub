#pragma once

#include <vector>

#include "ArmorModel.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            using ArmorModelPtrArray = std::vector<Common::ArmorModelPtr>;

            class IArmorQueries
            {
            public:
                virtual ~IArmorQueries() = default;

                inline ArmorModelPtrArray getCharacters(int charcterId) const
                {
                    return getCharactersImpl(charcterId);
                }

            private:
                virtual ArmorModelPtrArray getCharactersImpl(int charcterId) const = 0;
            };

        }
    }
}