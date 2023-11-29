#pragma once
#include <glm/glm.hpp>
#include <cstdint>

namespace dbrt
{

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
	return (((uint8_t)color.r*255) << 24) | (((uint8_t)color.g*255) << 16) | (((uint8_t)color.b*255) << 8) | ((uint8_t)color.a)cstdint
}
