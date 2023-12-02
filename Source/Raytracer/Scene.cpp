#include "Scene.h"
#include "mathutils.h"
#include <iostream>

void Scene::Render(Canvas& canvas)
{
	// cast ray for each point (pixel) on the canvas
	for (int y = 0; y < canvas.GetSize().y; y++)
	{
		for (int x = 0; x < canvas.GetSize().x; x++)
		{

			// create vec2 pixel from canvas x,y

			glm::vec2 pixel = { x , y };
			// get normalized (0 - 1) point coordinates from pixel
			//<get normalized point coordinates from pixel>
			glm::vec2 point = { pixel.x / canvas.GetSize().x, pixel.y / canvas.GetSize().y };

			// flip y
			point.y = 1.0f - point.y;

			// create ray from camera
			//<get ray from camera using point>
			ray_t ray = m_camera->GetRay(point);

			raycastHit_t raycastHit;
			color3_t color = Trace(ray, 0, 100, raycastHit);

			// draw color to canvas point (pixel)
			canvas.DrawPoint(pixel, color4_t(color, 1));
			// cast ray into scene
			// set color value from trace
		}
	}

}

color3_t Scene::Trace(const ray_t& ray)
{
		glm::vec3 direction = glm::normalize(ray.direction);
		// set scene sky color
		float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
		color3_t color = lerp(m_bottomColor,m_topColor,t);
		//std::cout << "direction: " << direction.x << " " << direction.y << " " << direction.z << std::endl;
			return color;
	}

color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit)
{
	bool rayHit = false;
	float closestDistance = maxDistance;

	// check if scene objects are hit by the ray
	for (int i = 0; i < m_objects.size(); i++)
	{
		// when checking objects don't include objects farther than closest hit (starts at max distance)
		if (m_objects[i]->Hit(ray, minDistance, closestDistance, raycastHit))
		{
			rayHit = true;
			// set closest distance to the raycast hit distance (only hit objects closer than closest distance)
			closestDistance = raycastHit.distance;
		}
	}

	// if ray hit object, scatter (bounce) ray and check for next hit
	if (rayHit)
	{
		ray_t scattered;
		color3_t color;

		if (raycastHit.material->Scatter(ray, raycastHit, color, scattered))
		{
			//raaycast hit normal as color
			color = -raycastHit.normal;

			//float normalizedValue = (raycastHit.distance / maxDistance);
			//normalizedValue = std::min(std::max(normalizedValue, 0.0f), 1.0f); // Clamp between 0 and 255

			//color = color3_t{ normalizedValue, normalizedValue, normalizedValue };
			//color = normalize({ raycastHit.distance, raycastHit.distance, raycastHit.distance });
			
			return color;

			//return color;
			
		}
		else
		{
			return color3_t{ 0, 0, 0 };
		}
	}

	// if ray not hit, return scene sky color
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
	color3_t color = lerp(m_bottomColor, m_topColor, t);

	return color;
}
