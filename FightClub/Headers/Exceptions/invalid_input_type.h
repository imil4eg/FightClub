#pragma once

#include <string>
#include <exception>

namespace fightclub
{
	namespace exceptions
	{
		class invalid_input_type : std::exception
		{
		public:
			invalid_input_type(const std::string& message) :
				std::exception(message.c_str())
			{
			}
		};
	}
}