#include "dbrt.h"
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
	Canvas canvas(400,300, renderer);
	
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene = Scene(glm::vec3{ 0.607f,0.294f,0.294f },glm::vec3{0.2f,0.2f,0.2f});// = Scene(glm::vec3{ 0,1,0}, glm::vec3{ 1,1,1} ); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);


	bool quit = false;
	while (!quit)
	{
		canvas.Clear({0.0f,0.0f,0.0f,1});
	//	for(int i = 0; i < 1000; i++) canvas.DrawPoint({randomMinMax(0,canvas.GetSize().x),randomMinMax(0,canvas.GetSize().y)},{random(),random(),random(),1});
	scene.Render(canvas);
		canvas.Update();
		renderer.PresentCanvas(canvas);

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
