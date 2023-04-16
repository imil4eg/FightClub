#pragma once

#include <boost/noncopyable.hpp>

#include "ICharacterQueries.hpp"

#include "IAbilityQueries.hpp"
#include "IAttributeQueries.hpp"
#include "IInventoryQueries.hpp"
#include "IQueryExecutor.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            class CharacterQueries : public ICharacterQueries, private boost::noncopyable
            {
            public:
                CharacterQueries(Common::IQueryExecutor& queryExeuctor, IInventoryQueries& inventoryQueries,
                                IAttributeQueries& attributeQueries, IAbilityQueries& abilityQueries) :
                    m_queryExecutor(&queryExeuctor),
                    m_inventoryQueries(&inventoryQueries),
                    m_attributeQueries(&attributeQueries),
                    m_abilityQueries(&abilityQueries)
                {
                }

            private:
                Common::CharacterModelPtr getByUserIdImpl(int userId) const override;
                bool doesExistImpl(int userId) const override;

                Common::QueryResult get(int userId) const;

            private:
                Common::IQueryExecutor* m_queryExecutor;
                IInventoryQueries* m_inventoryQueries;
                IAttributeQueries* m_attributeQueries;
                IAbilityQueries* m_abilityQueries;
            };

        }
    }
}