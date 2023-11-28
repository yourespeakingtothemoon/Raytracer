#pragma once
#include "Math.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ray_t
{
	ray_t()= default;
	ray_t(const glm::vec3& origin, const glm::vec3& direction) : origin(origin), direction(direction) {}

glm::vec3	GetPoint(float distance) const { return origin + direction * distance; }

	glm::vec3 origin;
	glm::vec3 direction;

};