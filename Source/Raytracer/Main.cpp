#include "dbrt.h"
#include <glm/glm.hpp>
#include <time.h>
#include <iostream>
#include <memory>
//main

	//parameters
const int width = 400;
const int height = 300;
const int samples = 20;
const int depth = 5;


	void InitScene01(Scene& scene, const Canvas& canvas)
	{
		float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
		std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
		scene.SetCamera(camera);

		// create objects -> add to scene
		for (int x = -10; x < 10; x++)
		{
			for (int z = -10; z < 10; z++)
			{
				std::shared_ptr<Material> material;

				// create random material

				float r = random();
				if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::vec3{ randomMinMax(0, 360), 1.0f, 1.0f });
				else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ randomMinMax(0.5f, 1.0f) }, randomMinMax(0, 0.5f));
				else if (r < 0.9f)	material = std::make_shared<Dielectric>(glm::vec3{ 1.0f,1.0f,1.0f }, randomMinMax(1.1f, 2));
				else				material = std::make_shared<Emissive>(glm::vec3{ randomMinMax(0, 360), 1.0f, 1.0f }, 5.0f);

				//		// set random sphere radius
				float radius = randomMinMax(0.2f, 0.3f);
				// create sphere using random radius and material
				auto sphere = std::make_unique<Sphere>(glm::vec3{ x + randomMinMax(-0.5f, 0.5f), radius, z + randomMinMax(-0.5f, 0.5f) }, radius, material);
				// add sphere to the scene
				scene.AddObject(std::move(sphere));
			}
		}

		auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
		scene.AddObject(std::move(plane));
	}

	void InitScene02(Scene& scene, const Canvas& canvas)
	{
		float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
		std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
		scene.SetCamera(camera);

		//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
		//scene.AddObject(std::move(triangle));

		auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
		scene.AddObject(std::move(plane));

		auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
		mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
		scene.AddObject(std::move(mesh));
	}



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
	if (!renderer.RenderWindow("Raytracer", width, height))
	{
		std::cout << "Failed to render window" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Window rendered" << std::endl;
	}
	Canvas canvas(width,height, renderer);
	
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	//std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	Scene scene( glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });
	
	
	//auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	//mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	//scene.AddObject(std::move(mesh));

	InitScene01(scene, canvas);
	
		canvas.Clear({0.0f,0.0f,0.0f,1});
	scene.Render(canvas,samples,depth);
		canvas.Update();
	//scene.AddObject(std::move(sphere));

	bool quit = false;
	while (!quit)
	{
	//	for(int i = 0; i < 1000; i++) canvas.DrawPoint({randomMinMax(0,canvas.GetSize().x),randomMinMax(0,canvas.GetSize().y)},{random(),random(),random(),1});
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
	/*const time_t* now = new time_t;
	SDL_Surface* surface = SDL_GetWindowSurface(renderer.m_window);
	const char* path = "C:/Users/toohi/Pictures/RaytracerScreenshots/"+ std::localtime(now)->tm_min;
	const char* file = "sshot.bmp";
	path.concat(file);
	SDL_SaveBMP(surface, path + "sshot.bmp");
	SDL_FreeSurface(surface);*/

	renderer.Shutdown();


	//std::cout << "Hello World!" << std::endl;
	return 0;
}


