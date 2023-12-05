#include "dbrt.h"

#include <memory>
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

	Scene scene = Scene(20,glm::vec3{ 0.0f,0.5f,0.5f },glm::vec3{0.8f,0.0f,0.0f});// = Scene(glm::vec3{ 0,1,0}, glm::vec3{ 1,1,1} ); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);
	// create material
	// create material
	//auto lambertian = std::make_shared<Lambertian>(color3_t{ randomMinMax(0,1), randomMinMax(0,1), randomMinMax(0,1) });
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0.8f,0.8f,0.0f });
	//auto metal = std::make_shared<Metal>(color3_t{ randomMinMax(0,1), randomMinMax(0,1), randomMinMax(0,1) }, 0.0f);
	auto metal = std::make_shared<Metal>(color3_t{ 0.8f,0.6f,0.2f }, 0.0f);

	// create objects -> add to scene
	for (int i = 0; i < 100; i++)
	{
		std::shared_ptr<Material> material = (rand() % 2) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(glm::vec3{ randomMinMax(-5,5),randomMinMax(-5,5),randomMinMax(-5,5) }, 0.5f, material);
		scene.AddObject(std::move(sphere));
	}// = std::make_unique<Sphere>(glm::vec3{ 0,0,10 }, 0.5f, material);

	//auto sphere = std::unique_ptr<Sphere>(glm::vec3{ 1,1,1}, <radius>, material);
	//scene.AddObject(std::move(sphere));

	bool quit = false;
	while (!quit)
	{
		canvas.Clear({0.0f,0.0f,0.0f,1});
	//	for(int i = 0; i < 1000; i++) canvas.DrawPoint({randomMinMax(0,canvas.GetSize().x),randomMinMax(0,canvas.GetSize().y)},{random(),random(),random(),1});
	scene.Render(canvas,50);
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
