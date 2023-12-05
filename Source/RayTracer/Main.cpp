#include <memory>
#include "Renderer.h"
#include "Random.h"
#include "Camera.h"
#include "Canvas.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"


	int main(int argc, char* argv[])
	{
		std::cout << "hello world!" << std::endl;

		seedRandom((int)time(nullptr));

		//<create renderer>
		Renderer renderer;
		//<initialize renderer>
		renderer.Initialize();
		//<create renderer window with size of x, y>
		renderer.CreateWindow("RayTracer", 800, 600);

		Canvas canvas(800, 600, renderer);

		float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
		std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 5 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

		Scene scene(20); // sky color could be set with the top and bottom color
		scene.SetCamera(camera);

		// create material
		auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
		auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

		// create objects -> add to scene
		for (int i = 0; i < 10; i++)
		{ //<use rand() and %to randomly pick the material>
			std::shared_ptr<Material> material = rand() % 2 ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
			//<create the sphere with the material>
			auto sphere = std::make_unique<Sphere>(glm::vec3{ random(-3, 3), random(-3, 3), random(-3, 0) }, 0.5f, material);
			scene.AddObject(std::move(sphere));
		}

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
				canvas.DrawPoint({ random(0, 800), random(0, 600) }, { random(0,1), random(0,1), random(0,1), 1 });
			}
			canvas.Update();
			*/
			
			canvas.Clear({ 0, 0, 0, 1 });
			scene.Render(canvas);
			canvas.Update();

			renderer.PresentCanvas(canvas);

		}

		//<shutdown renderer>
		renderer.Shutdown();

		return 0;
	}