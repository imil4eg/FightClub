#pragma once

#include <boost/noncopyable.hpp>

#include "CharacterModel.hpp"
#include "ICommandHandler.hpp"
#include "IQueryExecutor.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            class CreateCharacterCommand : public Common::ICommand
            {
            public:
                explicit CreateCharacterCommand(int userId, Common::CharacterType characterType) : 
                    m_userId(userId),
                    m_characterType(characterType)
                {
                }

                inline int getUserID() const
                {
                    return m_userId;
                }

                inline Common::CharacterType getCharacterType() const
                {
                    return m_characterType;
                }

            private:
                int m_userId;
                Common::CharacterType m_characterType;
            };

            class CreateCharacterCommandHandler : public Common::ICommandHandler, private boost::noncopyable
            {
            public:
                explicit CreateCharacterCommandHandler(Common::IQueryExecutor& queryExecutor) :
                    m_queryExecutor(&queryExecutor)
                {
                }

            private:
                void handleImpl(Common::ICommand& command) const override;

            private:
                Common::IQueryExecutor* m_queryExecutor;

                static const int characterStartHealth = 100;
                static const int characterStartDamage = 5;
                static const int characterStartAttributesValue = 10;
            };

        }
    }
}