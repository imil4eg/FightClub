#pragma once

#include "AttributeModel.hpp"

namespace FightClub {
    namespace Server {
        namespace Character {

            class IAttributeQueries
            {
            public:
                virtual ~IAttributeQueries() = default;

                Common::AttributeModelPtr get(int id) const 
                {
                    return getImpl(id);
                }

            private:
                virtual Common::AttributeModelPtr getImpl(int id) const = 0;
            };

        }
    }
}