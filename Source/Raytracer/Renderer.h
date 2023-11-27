#pragma once
#include <string>
#include <SDL.h>
class Renderer
{
public:
	Renderer();
	
	bool Initialize();
	void Shutdown();
	bool RenderWindow(const std::string& title, int width, int height);

private:
	SDL_Window* m_window{ 0 };
	SDL_Renderer* m_renderer{ 0 };
};