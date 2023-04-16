#include "CreateCharacterCommandHandler.hpp"

#include "TableColumnsNames.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            void CreateCharacterCommandHandler::handleImpl(Common::ICommand& command) const
            {
                auto& createCharacterCommand = static_cast<CreateCharacterCommand&>(command);

                Common::QueryResult result{
                    m_queryExecutor->executeSingleResult("INSERT INTO Attributes (Health, Damage, Strength, Agility) VALUES (?, ?, ?, ?)",
                {
                    characterStartHealth,
                    characterStartDamage,
                    characterStartAttributesValue,
                    characterStartAttributesValue
                },
                {
                    TableColumnsNames::ID
                })};

                int attributeID = result[TableColumnsNames::ID].toInt();

                m_queryExecutor->execute("INSERT INTO Characters (CharacterType, UserID, AttributeID) VALUES (?, ?, ?)",
                {
                    static_cast<int>(createCharacterCommand.getCharacterType()),
                    createCharacterCommand.getUserID(),
                    attributeID
                });
            }

        }
    }
}