#pragma once

#include "InventoryModel.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            class IInventoryQueries
            {
            public:
                virtual ~IInventoryQueries() = default;

                inline Common::InventoryModelPtr getByCharacterId(int characterId) const
                {
                    return getByCharacterIdImpl(characterId);
                }

            private:
                virtual Common::InventoryModelPtr getByCharacterIdImpl(int userId) const = 0;
            };

        }
    }
}