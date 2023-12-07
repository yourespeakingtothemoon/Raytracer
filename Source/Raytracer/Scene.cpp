#include "Scene.h"
#include "mathutils.h"
#include <iostream>
#include <iomanip>

void Scene::Render(Canvas& canvas, int numSamples, int depth)
{
	// cast ray for each point (pixel) on the canvas
	for (int y = 0; y < canvas.GetSize().y; y++)
	{
		for (int x = 0; x < canvas.GetSize().x; x++)
		{

			// create vec2 pixel from canvas x,y

			glm::vec2 pixel = { x , y };
			// get normalized (0 - 1) point coordinates from pixel
		// set initial color
			color3_t color{ 0 };
			// cast a ray for each sample, accumulate color value for each sample
			// each ray will have a random offset
			for ( int i = 0; i < numSamples; i++)
			{
				// get normalized (0 - 1) point coordinates from pixel
				// add random x and y offset (0-1) to each pixel
				glm::vec2 point = (pixel + glm::vec2{random(),random()})/ glm::vec2{canvas.GetSize().x,canvas.GetSize().y};
				// flip y
				point.y = 1.0f - point.y;

				// create ray from camera
				ray_t ray = m_camera->GetRay(point);

				// cast ray into scene
				// add color value from trace
				raycastHit_t raycastHit;
				color += Trace(ray, 0, 100, raycastHit, depth);
			}

			// draw color to canvas point (pixel)
			// get average color (average = (color + color + color) / number of samples)
			color/= numSamples;
				canvas.DrawPoint(pixel, color4_t(color, 1));
		}
		//display render progress
	DisplayProgress(y,canvas.GetSize().y);
		std::cout << std::setprecision(2) << std::setw(5) << ((y/canvas.GetSize().y) * 100.0f) << "%\n";
	}

	
	


}
void Scene::DisplayProgress(int currentRow, int totalRows) const
{
	std::cout << std::setprecision(2) << std::setw(5) << ((static_cast<float>(currentRow) / totalRows) * 100.0f) << "%\n";
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

color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth)
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

		// check if maximum depth (number of bounces) is reached, get color from material and scattered ray
		if (depth > 0 && raycastHit.material->Scatter(ray, raycastHit, color, scattered))
		{
			// recursive function, call self and modulate colors of depth bounces
			return color * Trace(scattered, minDistance, maxDistance, raycastHit, depth - 1);
		}
		else
		{
			// reached maximum depth of bounces (get emissive color, will be black except for Emissive materials)
			return raycastHit.material->GetEmissive();
		}


		if (raycastHit.material->Scatter(ray, raycastHit, color, scattered))
		{
			//raaycast hit normal as color
			//color = -raycastHit.normal;

			//float normalizedValue = (raycastHit.distance / maxDistance);
			//normalizedValue = std::min(std::max(normalizedValue, 0.0f), 1.0f); // Clamp between 0 and 255

			//color = color3_t{ normalizedValue, normalizedValue, normalizedValue };
			//color = normalize({ raycastHit.distance, raycastHit.distance, raycastHit.distance });


			//color *= raycastHit.distance;
			if (depth > 0 && raycastHit.material->Scatter(ray, raycastHit, color, scattered))
			{
				// recursive function, call self and modulate (multiply) colors of depth bounces
				return color * Trace(scattered, minDistance, maxDistance, raycastHit, depth - 1);
			}
			else
			{
				// reached maximum depth of bounces (color is black)
				return color3_t{ 0, 0, 0 };
			}

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

