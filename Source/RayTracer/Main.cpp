#include <memory>
#include "SDL.h"
#include "Renderer.h"
#include "MathUtils.h"
#include "Ray.h"
#include "Color.h"
#include "Canvas.h"
#include <random>
#include "Random.h"

namespace nc
{
	int main(int argc, char* argv[])
	{
		std::cout << "hello world!\n";

		//<create renderer>
		Renderer renderer = Renderer();
		//<initialize renderer>
		Renderer().Initialize();
		//<create renderer window with size of 400, 300>
		Renderer().CreateWindow("RayTracer", 400, 300);

		Canvas canvas(400, 300, renderer);

		//Scene scene; // sky color == top and bottom color
		//scene.SetCamera(camera);

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
			}
		}

		
		//canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 1000; i++)
		{
			canvas.DrawPoint({ random(0, 400), random(0, 300) }, { random01(), random01(), random01(), 1 });
		}
		canvas.Update();
		

		//canvas.Clear({ 0, 0, 0, 1 });
		//scene.Render(canvas);
		//canvas.Update();

		renderer.PresentCanvas(canvas);

		//<shutdown renderer>
		renderer.Shutdown();

		return 0;
	}

}