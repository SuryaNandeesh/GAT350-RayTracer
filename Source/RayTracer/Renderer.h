#pragma once
#include <string>
#include <SDL.h>
#include <SDL_main.h>
#include <iostream>
namespace nc 
{
	class Renderer
	{
	public:
		Renderer() = default;

		bool Initialize();
		void Shutdown();
		bool CreateWindow(const std::string& title, int width, int height);

	private:
		//<pointer to SDL_Window, set default value to nullptr>
		SDL_Window* m_window = nullptr;

		//<pointer to SDL_Renderer, set default value to nullptr>
		SDL_Renderer* m_renderer = nullptr;

	};
}