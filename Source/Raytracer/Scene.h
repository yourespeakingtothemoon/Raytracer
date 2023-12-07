#pragma once
#include "color.h"
#include "canvas.h"
#include "Ray.h"
#include "Camera.h"
#include "Shapes.h"
#include <memory>


class Scene
{
public:
	Scene() = default;
	Scene(const color3_t& top, const color3_t& bottom) :
	
	m_topColor{top},
	m_bottomColor{bottom}
	{}

void Render(class Canvas& canvas, int numSamples, int depth);

//helper function to display progess
void DisplayProgress(int currentRow, int totalRows) const;

color3_t Trace(const ray_t& ray);

void SetCamera(std::shared_ptr<Camera> cam) {m_camera = cam;}

color3_t Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth);

void AddObject(std::unique_ptr<Object> object) { m_objects.push_back(std::move(object)); }
void AddObject(std::unique_ptr<Sphere> object) { m_objects.push_back(std::move(object)); }

private:
std::shared_ptr<Camera> m_camera;

color3_t m_topColor{0};
color3_t m_bottomColor{1};
// depreciated int m_depth{ 5 };

//<vector of unique pointers to Object> m_objects;
std::vector<std::unique_ptr<Object>> m_objects;

};
