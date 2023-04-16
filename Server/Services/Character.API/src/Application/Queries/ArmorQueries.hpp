#pragma once

#include <boost/noncopyable.hpp>

#include "IArmorQueries.hpp"
#include "IAttributeQueries.hpp"
#include "IQueryExecutor.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            class ArmorQueries : public IArmorQueries, private boost::noncopyable
            {   
            public:
                ArmorQueries(Common::IQueryExecutor& queryExecutor, IAttributeQueries& attributeQueries) :
                    m_queryExecutor(&queryExecutor),
                    m_attributeQueries(&attributeQueries)
                {
                }

            private:
                ArmorModelPtrArray getCharactersImpl(int charcterId) const override;

            private:
                Common::IQueryExecutor* m_queryExecutor;
                IAttributeQueries* m_attributeQueries;
            };

        }
    }
}