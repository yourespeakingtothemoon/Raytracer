#pragma once
#include <cstdlib>
#include <algorithm>


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

inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max)
{
	return glm::vec3{ randomMinMax(min.x,max.x), randomMinMax(min.y,max.y), randomMinMax(min.z,max.z) };
}
inline glm::vec3 randomInUnitSphere()
{
	glm::vec3 v;
	// generate random vectors between -1 <-> +1, return vector if length is less than 1
	do
	{
		v = glm::vec3{ randomMinMax(-1,1), randomMinMax(-1,1), randomMinMax(-1,1) };
	} while (glm::length(v) >= 1.0f);

		return v;
}
