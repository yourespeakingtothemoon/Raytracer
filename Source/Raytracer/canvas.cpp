#include "canvas.h"
#include "Renderer.h"

#include <algorithm>

Canvas::Canvas(int w, int h, const Renderer& renderer)
{
	m_size = { w,h };
	m_texture = SDL_CreateTexture(renderer.m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w, h);

	m_buffer.resize(w * h);
}

Canvas::~Canvas()
{
	if(m_texture){
SDL_DestroyTexture(m_texture);
	
	}
}

void Canvas::Update()
{
	SDL_UpdateTexture(m_texture, NULL, m_buffer.data(), m_size.x * sizeof(color4_t));
}

void Canvas::Clear(const color4_t& ccolor)
{

	rgba_t rgba = ColorToRGBA(ccolor);
	std::fill(m_buffer.begin(), m_buffer.end(), rgba);
	

}

void Canvas::DrawPoint(const glm::ivec2& point, const color4_t& dcolor)
{
	if (point.x < 0 || point.y < 0 || point.x >= m_size.x || point.y >= m_size.y)
	{
	return;	
	}
	m_buffer[point.x + (point.y * m_size.x)] = ColorToRGBA(dcolor);
}
