#pragma once
#include <string>
#include <SDL.h>

	class Canvas;

class Renderer
{
public:
	Renderer();
	
	bool Initialize();
	void Shutdown();
	bool RenderWindow(const std::string& title, int width, int height);

	void PresentCanvas(const Canvas& cv);

	//friend class canvas;
	SDL_Renderer* m_renderer{ 0 };
	SDL_Window* m_window{ 0 };
private:
};
