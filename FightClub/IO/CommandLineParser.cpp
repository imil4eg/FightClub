#include "IO/CommandLineParser.h"

namespace fightclub
{
	namespace io
	{
		std::string CommandLineParser::getValue(const std::string& text, const std::string& parameterName) const
		{
			auto posFound{ text.find(parameterName) };

			if (posFound == std::string::npos)
			{
				return "";
			}

			std::string value{};
			posFound += SpaceBetweenAttributeAndValue;
			while (text[posFound] != ' ' && posFound < text.size())
			{
				value += text[posFound];
				++posFound;
			}

			return value;
		}
	}
}