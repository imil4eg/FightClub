#pragma once

#include <memory>

#include "ControllerCommon.hpp"
#include "Mediator.hpp"
#include "ICharacterQueries.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            class CharacterController : private boost::noncopyable
            {
            public:
                CharacterController(ICharacterQueries& characterQueries,
                                    Common::Mediator& mediator,
                                    Common::RequestProcesserContainer& requestProcessersContainer);

                json create(const json& request);
                json getByUserId(const json& request);
                json update(const json& request);

            private:
                ICharacterQueries* m_characterQueries;
                Common::Mediator* m_mediator;
            };

        }
    }
}