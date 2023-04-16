#pragma once

#include <boost/noncopyable.hpp>

#include "ICommandHandler.hpp"
#include "OptionalDefinitions.hpp"
#include "IQueryExecutor.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            class UpdateCharacterCommand : public Common::ICommand 
            {
            public:
                UpdateCharacterCommand(int id, Common::optionalID_t headId, Common::optionalID_t cuirassId,
                                        Common::optionalID_t bootsId, Common::optionalID_t weaponId) :
                                        m_id(id),
                                        m_headId(headId),
                                        m_cuirassId(cuirassId),
                                        m_bootsId(bootsId),
                                        m_weaponId(weaponId)
                {
                }

                inline int getId() const
                {
                    return m_id;
                }

                inline Common::optionalID_t getHeadId() const
                {
                    return m_headId;
                }

                inline Common::optionalID_t getCuirassId() const
                {
                    return m_cuirassId;
                }

                inline Common::optionalID_t getBootsId() const
                {
                    return m_bootsId;
                }

                inline Common::optionalID_t getWeaponId() const
                {
                    return m_weaponId;
                }

            private:
                int m_id;
                Common::optionalID_t m_headId;
                Common::optionalID_t m_cuirassId;
                Common::optionalID_t m_bootsId;
                Common::optionalID_t m_weaponId;
            };

            class UpdateCharacterCommandHandler : public Common::ICommandHandler, private boost::noncopyable
            {
            public:
                explicit UpdateCharacterCommandHandler(Common::IQueryExecutor& queryExecutor) :
                    m_queryExecutor(&queryExecutor)
                {
                }

            private:
                void handleImpl(Common::ICommand& command) const override;

            private:
                Common::IQueryExecutor* m_queryExecutor;
            };
        }
    }
}