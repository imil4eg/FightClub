#pragma once

#include <optional>

#include <QtCore/QVariant>

namespace FightClub {
    namespace Server {
        namespace Common {

            template<typename T>
            QVariant getOptionalValueOrNull(std::optional<T> value)
            {
                if (value.has_value())
                    return value.value();
                
                if (std::is_same<T, int>::value)
                {
                    return QVariant(QVariant::Int);
                }
                else if (std::is_same<T, std::string>::value)
                {
                    return QVariant(QVariant::String);
                }
                
                throw std::runtime_error("Unsupported optional type.");
            }

        }
    }
}