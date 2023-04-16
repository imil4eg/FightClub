#include "JsonConfigReader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace FightClub::Server::Common {

            ConfigDataPtr JsonConfigReader::getImpl(const std::string& name) const
            {
                std::ifstream file(m_configPath);
                json fileJson;
                file >> fileJson;   

                return constructInnerValue(fileJson[name]);
            }

            bool JsonConfigReader::tryGetImpl(const std::string& name, ConfigDataPtr& outValue) const
            {
                std::ifstream file(m_configPath);
                json fileJson;
                file >> fileJson;
                
                bool found{};
                if (fileJson.contains(name))
                {
                    outValue = constructInnerValue(fileJson[name]);
                    found = true;
                }
                
                return found;
            }

            ConfigDataPtr JsonConfigReader::constructInnerValue(const json& value) const
            {
                auto res = std::make_shared<ConfigData>();

                if (!value.is_array())
                {
                    res->value = value.get<std::string>();
                    return res;
                }

                for (auto it = value.begin(); it != value.end(); ++it)
                {
                    res->values.insert({it.key(), constructInnerValue(*it)});
                }

                return res;
            }
}