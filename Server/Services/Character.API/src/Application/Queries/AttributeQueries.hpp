#pragma once

#include <boost/noncopyable.hpp>

#include "IAttributeQueries.hpp"
#include "IQueryExecutor.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            class AttributeQueries : public IAttributeQueries, private boost::noncopyable
            {
            public:
                explicit AttributeQueries(Common::IQueryExecutor& queryExecutor) :
                    m_queryExecutor(&queryExecutor)
                {
                }

            private:
                Common::AttributeModelPtr getImpl(int id) const override;

            private:
                Common::IQueryExecutor* m_queryExecutor;
            }; 

        }
    }
}