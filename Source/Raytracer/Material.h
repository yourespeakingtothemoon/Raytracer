#pragma once
#include "Ray.h"
#include "random.h"
#include "mathutils.h"
#include "color.h"

class Material
{
public:
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const = 0;
	virtual color3_t GetEmissive() const { return color3_t{ 0 }; }
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

class Dielectric : public Material
{
public:
	Dielectric(const glm::vec3& albedo, float refractionIndex) : m_refractionIndex{ refractionIndex }, m_albedo{ albedo } {}
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const override;

protected:
	float m_refractionIndex = 0;
	glm::vec3 m_albedo{ 1 };

};

class Emissive : public Material
{
public:
	Emissive(const color3_t& albedo, float intensity =1.0f) : m_albedo{ albedo }, m_intensity{ intensity } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const override { return false; }
	color3_t GetEmissive() const override { return m_albedo * m_intensity; }

private:
	glm::vec3 m_albedo{ 1, 1, 1 };
	float m_intensity{ 1 };
};