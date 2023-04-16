#include "UpdateCharacterCommandHandler.hpp"

#include "OptionalHelpers.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            void UpdateCharacterCommandHandler::handleImpl(Common::ICommand& command) const
            {
                auto& updateCharacterCommand = static_cast<UpdateCharacterCommand&>(command);

                m_queryExecutor->execute("UPDATE Characters SET HeadID = ?, CuirassID = ?, BootsID = ?, WeaponID = ? WHERE ID = ?",
                {
                    updateCharacterCommand.getId(),
                    Common::getOptionalValueOrNull<int>(updateCharacterCommand.getHeadId()),
                    Common::getOptionalValueOrNull<int>(updateCharacterCommand.getCuirassId()),
                    Common::getOptionalValueOrNull<int>(updateCharacterCommand.getBootsId()),
                    Common::getOptionalValueOrNull<int>(updateCharacterCommand.getWeaponId())
                });
            }

        }
    }
}