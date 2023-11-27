#include <iostream>
#include "Renderer.h"
//main
int main(int argc, char** argv)
{
	//initalize Renderer
	Renderer renderer;
	if (!renderer.Initialize())
	{
		std::cout << "Failed to initialize renderer" << std::endl;
		return 1;
	}
	else
	{
				std::cout << "Renderer initialized" << std::endl;
	}
	//render window
	if (!renderer.RenderWindow("Raytracer", 400, 300))
	{
		std::cout << "Failed to render window" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Window rendered" << std::endl;
	}
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			//handle events
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			}
		}
	}

	renderer.Shutdown();


	//std::cout << "Hello World!" << std::endl;
	return 0;
}