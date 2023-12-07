#pragma once
#include <glm/glm.hpp>

#define FLT_EPSILON      1.192092896e-07F 

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

	inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n)
	{
		return v - 2.0f * dot(n,v) * n;
	}

	inline bool approx(float a, float b)
	{
		return fabsf(a - b) < FLT_EPSILON;
	}

	inline bool refract(const glm::vec3& v, const glm::vec3& n, float index, glm::vec3& refracted)
	{
		// normalize the incoming vector (v)
		glm::vec3 nv = glm::normalize(v);

		float dt = dot(nv, n);
		float discriminant = 1 - (index * index) * (1 - dt * dt);
		if (discriminant > 0)
		{
			refracted = index * (nv - (n * dt)) - (n * std::sqrt(discriminant));
			return true;
		}

		return false;
		}

	inline float schlick(float cosine, float index)
	{
		// calculate specular reflection coefficient, or probability of reflection
		float r0 = (1.0f - index) / (1 + index);
		r0 = r0 * r0;
		return r0 + (1.0f - r0) * (float)std::pow((1.0f - cosine), 5);
	}
