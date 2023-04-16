#pragma once

#include <boost/noncopyable.hpp>

#include "IWeaponQueries.hpp"
#include "IQueryExecutor.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            class WeaponQueries : public IWeaponQueries, private boost::noncopyable
            {
            public:
                explicit WeaponQueries(Common::IQueryExecutor& queryExecutor) :
                    m_queryExecutor(&queryExecutor)
                {
                }

            private:
                WeaponModelPtrArray getCharactersImpl(int id) const override;

            private:
                Common::IQueryExecutor* m_queryExecutor;
            };

        }
    }
}