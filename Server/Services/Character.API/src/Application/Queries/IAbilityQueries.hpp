#pragma once

#include "AbilityModel.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            class IAbilityQueries
            {
            public:
                virtual ~IAbilityQueries() = default;

                inline Common::AbilityModelPtrArray getByCharacterId(int characterId) const
                {
                    return getByCharacterIdImpl(characterId);
                }

            private:
                virtual Common::AbilityModelPtrArray getByCharacterIdImpl(int characterId) const = 0;
            };

        }
    }
}