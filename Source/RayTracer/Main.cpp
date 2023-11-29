#include <memory>
#include "SDL.h"
#include "Renderer.h"
#include "Ray.h"

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

		//<shutdown renderer>
		Renderer().Shutdown();

		return 0;
	}

}