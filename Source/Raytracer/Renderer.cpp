#include "Renderer.h"

Renderer::Renderer()
{
}

bool Renderer::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	return true;
}

void Renderer::Shutdown()
{
	if (m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = 0;
	}
	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = 0;
	}
	SDL_Quit();
}

bool Renderer::RenderWindow(const std::string& title, int width, int height)
{
	m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (!m_window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	return true;
}
