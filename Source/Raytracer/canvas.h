#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "color.h"

class Renderer;
struct SDL_Texture;

	class Canvas
	{
	public:
		Canvas(int w, int h, const Renderer& renderer);
		~Canvas();

		void Update();

		void Clear(const color4_t& ccolor);
		void DrawPoint(const glm::ivec2& point, const color4_t& dcolor);

		const glm::ivec2& GetSize() const { return m_size; }

		friend class Renderer;

		SDL_Texture* m_texture{ 0 };
	private:
		std::vector<rgba_t> m_buffer;
		glm::ivec2 m_size = { 0,0 };


	};

