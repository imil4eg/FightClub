#pragma once

#include <string>
#include <stdexcept>

namespace fightclub
{
	namespace common
	{
		class IntHelper
		{
		private:
			IntHelper() = delete;

		public:
			static bool tryParse(const std::string& value, int& outParsedValue)
			{
				try
				{
					outParsedValue = std::stoi(value);

					return true;
				}
				catch (std::invalid_argument)
				{
					return false;
				}
			}
		};
	}
}