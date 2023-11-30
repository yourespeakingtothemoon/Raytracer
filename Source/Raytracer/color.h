#pragma once
#include <glm/glm.hpp>
#include <cstdint>


typedef glm::vec3 color3_t;
typedef glm::vec4 color4_t;

typedef uint32_t rgba_t;

inline color4_t RGBAToColor(const rgba_t& rgba)
{
//red 24 green 16 blue 8 alpha nill

	float r = ((rgba >> 24) & 0xFF)  /255.0f;
	float g = ((rgba >> 16) & 0xFF) /255.0f;
	float b = ((rgba >> 8) & 0xFF) /255.0f;
	float a = (rgba & 0xFF)       /255.0f;

	return {r,g,b,a};
}

inline rgba_t ColorToRGBA(const color4_t& color)
{   
        uint8_t r = static_cast<uint8_t>(glm::clamp(color.r, 0.0f, 1.0f) * 255.0f);
        uint8_t g = static_cast<uint8_t>(glm::clamp(color.g, 0.0f, 1.0f) * 255.0f);
        uint8_t b = static_cast<uint8_t>(glm::clamp(color.b, 0.0f, 1.0f) * 255.0f);
        uint8_t a = static_cast<uint8_t>(glm::clamp(color.a, 0.0f, 1.0f) * 255.0f);

        return (r << 24) | (g << 16) | (b << 8) | a;
    
}
