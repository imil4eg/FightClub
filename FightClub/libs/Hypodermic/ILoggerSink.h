#pragma once

#include <string>

#include "LogLevel.h"


namespace Hypodermic
{

    class ILoggerSink
    {
    public:
        virtual ~ILoggerSink() = default;

        virtual void append(LogLevels::LogLevel level, const std::string& message) = 0;
    };

} // namespace Hypodermic