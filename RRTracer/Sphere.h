#ifndef SPHERE_H
#define SPHERE_H

#include "Tuple.h"

#include "Matrix.h"
#include "MatrixFactory.h"

#include "Material.h"

namespace RRT
{
	class Sphere
	{
	public:
		Sphere(const int& id) : id(id) {}

		inline int Id() const { return id; }

		inline Matrix Transform() const { return transform; }
		inline void Transform(const Matrix& new_transform) { transform = new_transform; }

		inline RRT::Material Material() const { return material; }
		inline RRT::Material& Material() { return material; }

	private:
		int id = 0;
		Tuple origin = { 0.0f, 0.0f, 0.0f, 1.0f };
		Matrix transform = RRT::MatrixFactory().IdentityMatrix();
		float radius = 0.0f;	
		RRT::Material material = RRT::Material();
	};
}

#endif // !SPHERE_H