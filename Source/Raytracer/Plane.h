#pragma once
#include "glm/glm.hpp"
#include "Object.h"



class Plane : public Object
{
public:
	Plane() = default;

	Plane(const glm::vec3& normal, const glm::vec3& center, std::shared_ptr<Material> material) :
		Object{ material },
		m_normal{ glm::normalize(normal) },
		m_center{ center }
	{
		
	}

	bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;


private:
	glm::vec3 m_normal{ 0 };
	//float m_distance{ 0 };
	glm::vec3 m_center{ 0 };
};