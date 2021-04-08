#pragma once

#include <stdexcept>

namespace fightclub
{
	namespace core
	{
		namespace exceptions
		{
			class not_found_exception : public std::runtime_error
			{
			public:
				not_found_exception(const std::string& message) : 
					std::runtime_error(message.c_str())
				{
				}
			};
		}
	}
}