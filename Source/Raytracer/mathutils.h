#pragma once
#include <glm/glm.hpp>
template<typename T>
	inline T lerp(const T& start, const T& end, float time)
	{

		//std::cout << (start * (1 - time)) + (end * time).x;
		return (start * (1-time)) + (end * time);
	}

	inline glm::vec3 cross(const glm::vec3& A, const glm::vec3& B)
	{
		return {(A.y * B.z) - (A.z * B.y),
		(A.z * B.x) - (A.x * B.z),	
		(A.x * B.y) - (A.y * B.x)};
	}
	inline glm::vec3 normalize(const glm::vec3& A)
	{
		float length = sqrt((A.x * A.x) + (A.y * A.y) + (A.z * A.z));
		return {A.x / length, A.y / length, A.z / length};
	}

	inline float dot(const glm::vec3& v1, const glm::vec3& v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	}
