#pragma once

#include <ctime>
#include <random>

namespace fightclub
{
	namespace core
	{
		namespace common
		{
			class RandomGenerator
			{
			private:
				static std::mt19937 gen;

			public:
				static int getBetween(int min, int max);
			};
		}
	}
}