#pragma once




template<typename T>
	inline T lerp(const T& start, const T& end, float time)
	{
		return (start*(1-time)) + (start * end);
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
