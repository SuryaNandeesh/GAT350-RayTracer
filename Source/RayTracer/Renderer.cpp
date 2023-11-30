#include "Renderer.h"
#include <SDL.h>
#include <iostream>

namespace nc 
{
	bool Renderer::Initialize()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}
		return true;
	}

	void Renderer::Shutdown()
	{
		//<if SDL window is not null, destroy SDL window>
		if (m_window != nullptr) {
			SDL_DestroyWindow(m_window);
			m_window = nullptr;
		}

		//<if SDL renderer is not null, destroy SDL renderer>
		if (m_renderer != nullptr) {
			SDL_DestroyRenderer(m_renderer);
			m_renderer = nullptr;
		}
		SDL_Quit();
	}

	bool Renderer::CreateWindow(const std::string& title, int width, int height)
	{
		//<create SDL window(https://wiki.libsdl.org/SDL2/SDL_CreateWindow Links to an external site.) >
		m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
		if (!m_window)
		{
			std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return false;
		}

		//<create SDL renderer(https://wiki.libsdl.org/SDL2/SDL_CreateRenderer Links to an external site.) use flags SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC>
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!m_renderer)
		{
			std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(m_window);
			m_window = nullptr;
			SDL_Quit();
			return false;
		}
		return true;
	}
	void Renderer::PresentCanvas(const Canvas& canvas)
	{
		// copy canvas texture to renderer
		SDL_RenderCopy(m_renderer, canvas.m_texture, nullptr, nullptr);
		// present renderer to screen
		SDL_RenderPresent(m_renderer);
	}
};