#pragma once

#include <string>

namespace fightclub
{
	namespace io
	{
		class ICommandLineParser
		{
		public:
			virtual ~ICommandLineParser() = default;
			virtual std::string getValue(const std::string& text, const std::string& parameterName) const = 0;
		};
	}
}