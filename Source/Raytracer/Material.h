#pragma once
#include "Ray.h"
#include "random.h"
#include "mathutils.h"
#include "color.h"

class Material
{
public:
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const = 0;
};

class Lambertian : public Material
{
public:
	//Lambertian(<pass as const reference> albedo) : m_albedo{ albedo } {}
	Lambertian(const color3_t& albedo) : m_albedo{ albedo } {}
	//<override the parent Scatter() method>
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const override
	{
		//<generate a random point in the unit sphere>
		glm::vec3 target = raycastHit.point + raycastHit.normal + randomInUnitSphere();
		//<set the scattered ray to a ray from the hit point to the random point in the unit sphere>
		scattered = ray_t{ raycastHit.point, target - raycastHit.point };
		//<set the color to the albedo>
		color = m_albedo;
		return true;
	}

protected:
	color3_t m_albedo;
};