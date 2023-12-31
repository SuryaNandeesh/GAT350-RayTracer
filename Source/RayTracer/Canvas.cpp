#include "Canvas.h"
#include "Renderer.h"
#include <SDL.h>

	Canvas::Canvas(int width, int height, const Renderer& renderer)
	{
		m_size = { width, height };
		m_texture = SDL_CreateTexture(renderer.m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

		m_buffer.resize(width * height);
	}

	Canvas::~Canvas()
	{
		//<if m_texture not nullptr SDL Destroy Texture https ://wiki.libsdl.org/SDL2/SDL_DestroyTexture Links to an external site.>
		if (m_texture) SDL_DestroyTexture(m_texture);
	}

	void Canvas::Update()
	{
		// set texture with buffer rgba_t data
		//SDL_UpdateTexture(<https://wiki.libsdl.org/SDL2/SDL_UpdateTexture Links to an external site.>);
		SDL_UpdateTexture(m_texture, NULL, m_buffer.data(), m_size.x * sizeof(rgba_t));
	}

	void Canvas::Clear(const color4_t& color)
	{
		rgba_t rgba = ColorToRGBA(color);
		//std::fill(<fill m_buffer with rgba(https://en.cppreference.com/w/cpp/algorithm/fill Links to an external site.)>);
		std::fill(m_buffer.begin(), m_buffer.end(), rgba);
	}

	void Canvas::DrawPoint(const glm::ivec2& point, const color4_t& color)
	{
		if (point.x < 0 || point.y < 0 || point.x >= m_size.x || point.y >= m_size.y) return;
		m_buffer[point.x + (point.y * m_size.x)] = ColorToRGBA(color);
	}