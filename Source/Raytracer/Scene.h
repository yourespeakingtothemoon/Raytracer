#pragma once
#include "color.h"
#include "canvas.h"
#include "Ray.h"
#include "Camera.h"
#include <memory>


class Scene
{
public:
	Scene() = default;
	Scene(const color3_t& top, const color3_t& bottom) :
	m_topColor{top},
	m_bottomColor{bottom}
	{}

void Render(class Canvas& canvas);
color3_t Trace(const ray_t& ray);

void SetCamera(std::shared_ptr<Camera> cam) {m_camera = cam;}

private:
std::shared_ptr<Camera> m_camera;

color3_t m_topColor{0};
color3_t m_bottomColor{1};

};
