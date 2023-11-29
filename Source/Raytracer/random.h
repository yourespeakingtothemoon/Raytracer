#pragma once
#include <cstdlib>
#include <algorithm>

namespace dbrt
{

inline void seedRandom(unsigned int seed)
	{
	srand(seed);
	}
inline float random()
	{
	return (float)rand() / RAND_MAX;
	}
inline float randomMinMax(float min, float max)
	{
	if(min>max)
		{
		std::swap(min,max);
		}
	return min + random()*(max-min);

	}	

}
