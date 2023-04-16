#include <QtCore/QVariant>

#include "EnumClass.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            class DatabaseQueryDictionary : public EnumClass
            {
            public:
                static const QString& ParamaterHolder;
                static const QString& CommaAndSpace;
                static const QString& SetNewParameterPattern;
                static const QString& SelectAllColumns;
                
            };

        }
    }
}