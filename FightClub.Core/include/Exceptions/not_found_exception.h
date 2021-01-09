#pragma once

#include <stdexcept>

namespace fightclub
{
	namespace core
	{
		namespace exceptions
		{
			class not_found_exception : public std::exception
			{
			public:
				not_found_exception(const std::string& message) : 
					std::exception(message.c_str())
				{
				}
			};
		}
	}
}