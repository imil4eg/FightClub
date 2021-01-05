#pragma once

#include "ICommandLineParser.h"

namespace fightclub
{
	namespace io
	{
		class CommandLineParser : public ICommandLineParser
		{
		private:
			const int SpaceBetweenAttributeAndValue{ 3 };

		public:
			std::string getValue(const std::string& text, const std::string& parameterName) const override;
		};
	}
}