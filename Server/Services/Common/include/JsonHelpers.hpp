#pragma once

#include "JsonAttributes.hpp"
#include "JsonDefinitions.hpp"
#include "OptionalDefinitions.hpp"

namespace FightClub {
    namespace Server {
        namespace Common {

            inline json createErrorResponseTemplate(const std::string& error)
            {
                json response;
                response.emplace(JsonAttributes::message, error);

                return response;
            }

            template<typename T>
            void emplaceIDIfNotNull(json& json, const std::string& attributeName, const T* value)
            {
                if (value != nullptr)
                    json.emplace(attributeName, value->getId());
            }

            inline optionalID_t getIdOrNull(const json& json, const std::string& attributeName)
            {
                if (!json.contains(attributeName))
                    return std::nullopt;

                return optionalID_t(json[attributeName].get<int>());
            }

            template<typename T>
            void emplaceIfHasValue(json& text, const std::string& attributeName, std::optional<T> value)
            {
                if (value.has_value())
                    text.emplace(attributeName, value.value());
            }

            template<typename TValue>
            void setFromJsonOrNull(const json& json, std::optional<TValue>& field, const std::string& attributeName)
            {
                if (json.contains(attributeName))
                {
                    field = json[attributeName].get<TValue>();
                }
                else
                {
                    field = std::nullopt;
                }
            }
        }
    }
}