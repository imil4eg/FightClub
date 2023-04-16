#pragma once

#include <vector>

#include "WeaponModel.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            using WeaponModelPtrArray = std::vector<Common::WeaponModelPtr>;

            class IWeaponQueries
            {
            public:
                virtual ~IWeaponQueries() = default;

                inline WeaponModelPtrArray getCharacters(int characterId) const
                {
                    return getCharactersImpl(characterId);
                }

            private:
                virtual WeaponModelPtrArray getCharactersImpl(int characterId) const = 0;
            };

        }
    }
}