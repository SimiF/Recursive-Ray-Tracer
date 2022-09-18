#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

namespace RRT
{
	class Material
	{
	public:
		Material() = default;
		Material(const RRT::Color& color, const float& ambient, const float& diffuse, const float& specular, const float& shininess)
			: color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

		inline RRT::Color Color() const { return color; }
		inline void Color(const RRT::Color& c) { color = c; }
		inline RRT::Color& Color() { return color; }

		inline float Ambient() const { return ambient; }
		inline float Diffuse() const { return diffuse; }
		inline float Specular() const { return specular; }
		inline float Shininess() const { return shininess; }

		inline void Ambient(const float& a) { ambient = a; }
		inline void Diffuse(const float& d) { diffuse = d; }
		inline void Specular(const float& s) { specular = s; }
		inline void Shininess(const float& s) { shininess = s; }

	private:
		RRT::Color color = RRT::Color(1.0f, 1.0f, 1.0f);
		float ambient = 0.1f;
		float diffuse = 0.9f;
		float specular = 0.9f;
		float shininess = 200.0f;
	};
}

#endif // !MATERIAL_H