#pragma once

#include <string>
#include <stdexcept>

namespace fightclub
{
	namespace exceptions
	{
		class invalid_input_type : std::runtime_error
		{
		public:
			invalid_input_type(const std::string& message) :
				std::runtime_error(message.c_str())
			{
			}
		};
	}
}