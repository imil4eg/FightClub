#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <ctime>
#include <random>

class RandomGenerator
{
private:
	static std::mt19937 gen;

public:
	static int getBetween(int min, int max);
};


#endif // !RANDOM_GENERATOR_H
