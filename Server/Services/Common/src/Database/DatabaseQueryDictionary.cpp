#include "DatabaseQueryDictionary.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            const QString& DatabaseQueryDictionary::ParamaterHolder = "?";
            const QString& DatabaseQueryDictionary::CommaAndSpace = ", ";
            const QString& DatabaseQueryDictionary::SetNewParameterPattern = "=?, ";
            const QString& DatabaseQueryDictionary::SelectAllColumns = "*";

        }
    }
}