#include "dbrt.h"
#include <glm/glm.hpp>
#include <time.h>
#include <iostream>
#include <memory>
//main

	//parameters
const int width = 1920;
const int height = 1080;
const int samples = 1;
const int depth = 6;


void CornellBox(Scene& scene, const Canvas& canvas);
void SpaceScene(Scene& scene, const Canvas& canvas);
void RandomSphereScene(Scene& scene, const Canvas& canvas);





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
	Scene scene(glm::vec3{ 0.25f,0.0f,0.25f }, glm::vec3{ 1.0f,1.0f,1.0f });
	

	
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


void CornellBox(Scene& scene, const Canvas& canvas)
{
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 5 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 40.0f, aspectRatio);

	scene.SetCamera(camera);


	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, -1, 0 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(plane));
	auto plane2 = std::make_unique<Plane>(glm::vec3{ 0, -1, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Emissive>(color3_t{ 1 }));
	scene.AddObject(std::move(plane2));

	auto leftWall = std::make_unique<Plane>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 2, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 0, 1, 0 }));
	scene.AddObject(std::move(leftWall));
	auto rightWall = std::make_unique<Plane>(glm::vec3{ 1, 0, 0 }, glm::vec3{ -2, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	scene.AddObject(std::move(rightWall));
	auto backWall = std::make_unique<Plane>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, -2 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(backWall));




	// Create and add two boxes
	/*auto box1 = std::make_unique<Mesh>(std::make_shared<Metal>(color3_t{ 1, 1, 1 },0));
	box1->Load("models/cube.obj", glm::vec3{ .5f, -0.5f, 1.5f }, glm::vec3{ 0, 45, 0 },glm::vec3{0.5f,1,1});*/
	auto box1 = std::make_unique<Sphere>(glm::vec3{ .5f, -0.5f, 1.5f }, 0.5f, std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0));
	scene.AddObject(std::move(box1));

	auto box2 = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0.2f, 0.2f, 0.2f }));
	box2->Load("models/cube.obj", glm::vec3{ -0.5f, -0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(box2));


}

void SpaceScene(Scene& scene, const Canvas& canvas)
{
	




	auto box1 = std::make_unique<Mesh>(std::make_shared<Metal>(color3_t{ 1, 0.5f, 0 }, 0.5f));
	box1->Load("models/ship.obj", glm::vec3{ 1.0f, -0.5f, 1.5f }, glm::vec3{ -15, -90, -10 }, glm::vec3{ 0.5f });
	scene.AddObject(std::move(box1));
	auto bbadguy = std::make_unique<Mesh>(std::make_shared<Metal>(color3_t{ 0, 1, 1 }, 0.5f));
	bbadguy->Load("models/ship.obj", glm::vec3{ -1.0f, 0.5f, 1.5 }, glm::vec3{ 8, 90, 10 }, glm::vec3{ 0.5f });
	scene.AddObject(std::move(bbadguy));
	auto laser = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t{ 0, 1, 0 }));
	laser->Load("models/bullet.fbx", glm::vec3{ 0, 0, 1.5 }, glm::vec3{ 0, 0, -15 }, glm::vec3{ 0.1f });
	scene.AddObject(std::move(laser));

	auto star = std::make_unique<Sphere>(glm::vec3{ -5, -3, 1.5 }, 4, std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0));
	scene.AddObject(std::move(star));

	for (int i = 0; i < 35; i++)
	{
		auto sphere = std::make_unique<Sphere>(glm::vec3{ randomMinMax(-10,10), randomMinMax(-10,10), -10 }, randomMinMax(0.01f, 0.1f), std::make_shared<Emissive>(color3_t{ 1, 1.0f, 1.0f }));
		scene.AddObject(std::move(sphere));
	}
	for (int i = 0; i < 5; i++)
	{
		std::string asteroid;
		int num = randomMinMax(0, 500);
		num >= 250 ? asteroid = "models/aster2-2.fbx" : asteroid = "models/rock3.fbx";

		//auto sphere = std::make_unique<Sphere>(glm::vec3{ randomMinMax(-10,10), randomMinMax(-10,10), -10 }, randomMinMax(0.01f, 0.1f), std::make_shared<Emissive>(color3_t{ 1, 1.0f, 1.0f }));
		auto aster = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ randomMinMax(0,1), randomMinMax(0,1), randomMinMax(0,1) }));
		aster->Load("models/bullet.fbx", glm::vec3{ randomMinMax(-10,10), randomMinMax(-5,5), -5 }, glm::vec3{ randomMinMax(0,360), randomMinMax(0,360), randomMinMax(0,360) });
		scene.AddObject(std::move(aster));
	}
	auto backWall = std::make_unique<Plane>(glm::vec3{ 0, 0, 20 }, glm::vec3{ 0, 0, -2 }, std::make_shared<Emissive>(color3_t{ 1 }));
	scene.AddObject(std::move(backWall));
}

void RandomSphereScene(Scene& scene, const Canvas& canvas)
{



}



	//InitScene01(scene, canvas);