#pragma once

#include <string>

namespace fightclub
{
	namespace core
	{
		namespace io
		{
			class IMessageDisplayer
			{
			public:
				virtual ~IMessageDisplayer() = default;
				virtual void display(const std::string& message) const = 0;
			};
		}
	}
}