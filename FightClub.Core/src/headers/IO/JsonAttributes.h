#pragma once

#include <string>

namespace fightclub
{
	namespace core
	{
		namespace io
		{
			class JsonAttributes
			{
			public:
				static const std::string& Id;
				static const std::string& Name;
				static const std::string& Damage;
				static const std::string& Type;
				static const std::string& Value;
				static const std::string& Armors;
				static const std::string& Weapons;
				static const std::string& Abilities;
				static const std::string& Cost;
				static const std::string& Duration;
				static const std::string& SelectedAbilities;
				
				JsonAttributes() = delete;
			};
		}
	}
}
