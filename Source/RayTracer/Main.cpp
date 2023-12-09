#include <memory>
#include "Renderer.h"
#include "Random.h"
#include "Camera.h"
#include "Color.h"
#include "Canvas.h"
#include "Scene.h"
#include "Material.h"
#include "MathUtils.h"
#include "Object.h"
#include "Sphere.h"
#include "glm/gtx/color_space.hpp"
#include "Plane.h"
#include "Mesh.h"
#include "Triangle.h"

void InitScene01(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	//scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	//auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	//mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	//scene.AddObject(std::move(mesh));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t{ 20 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
}

void InitSceneCornell(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 15 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	{
		auto plane = std::make_unique<Plane>(glm::vec3{ 0, -2, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 1 }));
		scene.AddObject(std::move(plane));
	}
	{
		auto plane = std::make_unique<Plane>(glm::vec3{ 0, 2, 0 }, glm::vec3{ 0, -1, 0 }, std::make_shared<Lambertian>(color3_t{ 1 }));
		scene.AddObject(std::move(plane));
	}
	{
		auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, -2 }, glm::vec3{ 0, 0, 1 }, std::make_shared<Lambertian>(color3_t{ 1 }));
		scene.AddObject(std::move(plane));
	}
	{
		auto plane = std::make_unique<Plane>(glm::vec3{ -2, 0, 0 }, glm::vec3{ 1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
		scene.AddObject(std::move(plane));
	}
	{
		auto plane = std::make_unique<Plane>(glm::vec3{ 2, 0, 0 }, glm::vec3{ -1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 0, 1, 0 }));
		scene.AddObject(std::move(plane));
	}
	{
		auto mesh = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t{ 20 }));
		mesh->Load("models/quad.obj", glm::vec3{ 0, 2, 0 }, glm::vec3{ 90, 0, 0 });
		scene.AddObject(std::move(mesh));
	}
	{
		auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1 }));
		mesh->Load("models/cube.obj", glm::vec3{ -1, -1.5f, 0 }, glm::vec3{ 0, 30, 0 });
		scene.AddObject(std::move(mesh));
	}
	{
		auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1, 1, 1 }));
		mesh->Load("models/cube.obj", glm::vec3{ 1, -1.5f, 1 }, glm::vec3{ 0, -10, 0 });
		scene.AddObject(std::move(mesh));
	}

}

void InitSceneFinal(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 15 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -6; x < 6; x++)
	{
		for (int z = -6; z < 6; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			std::unique_ptr<Object> object;
			// random radius
			float radius = random(0.2f, 0.3f);
			// randomizer for everything else
			float r2 = random01();
			if (r2 < 0.7f)
				object = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			else if (r2 < 0.8f)
			{
				object = std::make_unique<Mesh>(material);
				dynamic_cast<Mesh*>(object.get())->Load("models/cube.obj", glm::vec3{ x + random(-0.8f, 0.8f), 0.5, z + random(-0.8f, 0.8f) }, glm::vec3{ random(0, 360), random(0, 360), random(0, 360) }, glm::vec3{ 0.3 });
			}
			else
			{
				object = std::make_unique<Triangle>(glm::vec3{ x + random(-0.9f, 0), 0, z + random(-0.9f, 0.9f) }, glm::vec3{ x + random(0, 0.9f), 0, z + random(-0.9f, 0.9f) }, glm::vec3{ x + random(-0.9f, 0.9f), random(0.1f, 1), z + random(-0.9f, 0.9f) }, material);
			}
			// add object to the scene
			scene.AddObject(std::move(object));
		}
	}
	//plane so it doesnt just sit in the air, suspeneded
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}


int main(int argc, char* argv[])
{
	const int width = 800;
	const int height = 600;
	const int samples = 20;
	const int depth = 6;

	std::cout << "Hello World!" << std::endl;
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", width, height);

	Canvas canvas(width, height, renderer);
	Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f }); // sky color could be set with the top and bottom color // blue
	//Scene scene(glm::vec3{ 0.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f }); // sky color could be set with the top and bottom color //for making the emmisive box

	//InitSceneCornell(scene, canvas);
	//InitScene01(scene, canvas);
	//InitScene02(scene, canvas);
	InitSceneFinal(scene, canvas);

	// render scene
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, samples, depth);
	canvas.Update();

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}


		/*
		//canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 1000; i++)
		{
			canvas.DrawPoint({ random(0, 400), random(0, 300) }, { random01(), random01(), random01(), 1 });
		}
		canvas.Update();
		*/

		renderer.PresentCanvas(canvas);
	}

	renderer.Shutdown();

	return 0;
}