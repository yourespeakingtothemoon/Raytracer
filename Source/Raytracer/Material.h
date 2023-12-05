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
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const override;

protected:
	color3_t m_albedo;
};

class Metal : public Material
{
	public:
		Metal(const glm::vec3 & albedo, float fuzz) : m_albedo{ albedo }, m_fuzz{ fuzz } {}
		virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3 & color, ray_t& scattered) const override;

	protected:
		glm::vec3 m_albedo {0};
		float m_fuzz = 0;

};
