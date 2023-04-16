#pragma once

#include "IConfigReader.hpp"

#include "JsonDefinitions.hpp"

namespace FightClub {
    namespace Server { 
        namespace Common {

            class JsonConfigReader : public IConfigReader
            {
            public:
                JsonConfigReader(const std::string& path) :
                    m_configPath{path}
                {
                }

                ConfigDataPtr getImpl(const std::string& name) const override;
                bool tryGetImpl(const std::string& name, ConfigDataPtr& outValue) const override;

            private:
                ConfigDataPtr constructInnerValue(const json& value) const;

            private:
                std::string m_configPath;
            };

        }
    }
}