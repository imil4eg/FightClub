#pragma once

#include <string>

namespace fightclub
{
	namespace core
	{
		namespace io
		{
			class IInputProcesser
			{
			public:
				virtual ~IInputProcesser() = default;
				virtual std::string getLine() const = 0;
			};
		}
	}
}
