#pragma once

#include "CharacterModel.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            class ICharacterQueries
            {
            public:
                virtual ~ICharacterQueries() = default;
                
                inline Common::CharacterModelPtr getByUserId(int userId) const 
                {
                    return getByUserIdImpl(userId);
                }

                inline bool doesExist(int userId) const
                {
                    return doesExistImpl(userId);
                }

            private:
                virtual Common::CharacterModelPtr getByUserIdImpl(int userId) const = 0;
                virtual bool doesExistImpl(int userId) const = 0;
            };

        }
    }
}