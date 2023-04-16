#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace FightClub::Server::Common {

    struct ConfigData;
    using ConfigDataPtr = std::shared_ptr<ConfigData>;
    struct ConfigData
    {
        std::string value;
        std::unordered_map<std::string, std::string> attributes;
        std::unordered_map<std::string, ConfigDataPtr> values;
    };

    class IConfigReader
    {
    public:
        virtual ~IConfigReader() = default;

        inline ConfigDataPtr get(const std::string& name) const
        {
            return getImpl(name);
        }

        inline bool tryGet(const std::string& name, ConfigDataPtr& outValue) const
        {
            return tryGetImpl(name, outValue);
        }

    private:
        virtual ConfigDataPtr getImpl(const std::string& name) const = 0;
        virtual bool tryGetImpl(const std::string& name, ConfigDataPtr& outValue) const = 0;
    };
}