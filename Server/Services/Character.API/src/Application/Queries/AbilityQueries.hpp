#pragma once

#include <boost/noncopyable.hpp>

#include "IAbilityQueries.hpp"
#include "IQueryExecutor.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            class AbilityQueries : public IAbilityQueries, private boost::noncopyable
            {
            public:
                explicit AbilityQueries(Common::IQueryExecutor& queryExecutor) :
                    m_queryExecutor(&queryExecutor)
                {
                }

            private:
                Common::AbilityModelPtrArray getByCharacterIdImpl(int characterId) const override;
            
            private:
                Common::IQueryExecutor* m_queryExecutor;
            };

        }
    }
}