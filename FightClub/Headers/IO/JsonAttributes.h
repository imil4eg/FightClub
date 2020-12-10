#pragma once

#include <string>

namespace fightclub
{
	namespace io
	{
		class JsonAttributes
		{
		public:
			static const std::string Id;
			static const std::string Name;
			static const std::string Damage;
			static const std::string Type;
			static const std::string Value;
			static const std::string Armors;
			static const std::string Weapons;

			JsonAttributes() = delete;
		};
	}
}