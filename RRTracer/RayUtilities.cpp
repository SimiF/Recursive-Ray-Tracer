#include "RayUtilities.h"

namespace RRTRayUtils
{
	std::vector<RRT::Intersection> Intersects(const RRT::Sphere& sphere, const RRT::Ray& ray)
	{
		RRT::Ray transformed_ray = Transform(ray, sphere.Inverse());	
		std::vector<RRT::Intersection> xs_points(0);

		RRT::Tuple sphere_to_ray = transformed_ray.Origin() - RRT::TupleFactory().Point(0.0f, 0.0f, 0.0f);
		float a = RRTTupleUtils::Dot(transformed_ray.Direction(), transformed_ray.Direction());
		float b = 2 * RRTTupleUtils::Dot(transformed_ray.Direction(), sphere_to_ray);
		float c = RRTTupleUtils::Dot(sphere_to_ray, sphere_to_ray) - 1;
		float discriminant = b * b - (4 * a * c);

		if (discriminant >= 0)
		{
			xs_points.resize(2); 		
			
			const float denom = 2 * a;
			const float sqrt_func = sqrtf(discriminant);

			const float t1 = (-b - sqrt_func) / denom;
			const float t2 = (-b + sqrt_func) / denom;		

			if (t1 <= t2)
			{
				xs_points[0] = (RRT::Intersection(t1, sphere));
				xs_points[1] = (RRT::Intersection(t2, sphere));
			}
			else
			{
				xs_points[0] = (RRT::Intersection(t2, sphere));
				xs_points[1] = (RRT::Intersection(t1, sphere));
			}
		}

		return xs_points;
	}

	std::optional<RRT::Intersection> Hit(const std::vector<RRT::Intersection>& xs_vec)
	{
		bool hit_flag = false;		
		RRT::Intersection final_xs = RRT::Intersection(1e10f);

		for (const auto& xs : xs_vec)
		{
			if (xs.Time() > 0.0f && xs.Time() < final_xs.Time())
			{
				final_xs = xs;
				hit_flag = true;
			}
		}

		if (!RRTUtils::s_floats_equal(final_xs.Time(), 1e10f))
		{
			return final_xs;
		}

		return {};
	}

	RRT::Ray Transform(const RRT::Ray& ray, const RRT::Matrix& matrix)
	{	
		RRT::Tuple new_origin = matrix * ray.Origin();		
		RRT::Tuple new_direction = matrix * ray.Direction();
		RRT::Ray new_ray(new_origin, new_direction);

		return new_ray;
	}

	RRT::Tuple Normal_At(const RRT::Sphere& sphere, const RRT::Tuple& point)
	{		
		RRT::Tuple object_point = sphere.Inverse() * point;
		RRT::Tuple object_normal = object_point - RRT::TupleFactory().Point(0.0f, 0.0f, 0.0f);

		// vector cannot be multiplied by the inverse of the transform matrix alone as it will not preserve normal vector direction
		RRT::Tuple world_normal = RRTMatrixUtils::Transpose(sphere.Inverse()) * object_normal;

		// depending on matrix used, the w factor may be changed. Here we hard reset to this being a vector
		world_normal.W(0.0f);

		return RRTTupleUtils::Normalize(world_normal);
	}

	RRT::Tuple Reflect(const RRT::Tuple& in_vec, const RRT::Tuple& in_norm)
	{
		return in_vec - in_norm * 2 * RRTTupleUtils::Dot(in_vec, in_norm);
	}

	RRT::Color Lighting(const RRT::Material& material, const RRT::Tuple& point_at, const RRT::PointLight& light_source, const RRT::Tuple& eye_vec, const RRT::Tuple& norm_vec)
	{
		RRT::Color eff_color = material.Color() * light_source.Intensity();
		RRT::Tuple light_vec = RRTTupleUtils::Normalize(light_source.Position() - point_at);

		RRT::Color ambient_cont = eff_color * material.Ambient();
		RRT::Color diffuse_cont = RRT::Color();
		RRT::Color specular_cont = RRT::Color();

		float dot_normal = RRTTupleUtils::Dot(light_vec, norm_vec);
		if (dot_normal > 0.0f)
		{
			diffuse_cont = eff_color * material.Diffuse() * dot_normal;

			RRT::Tuple reflect_vec = Reflect(-light_vec, norm_vec);
			float reflect_dot_eye = RRTTupleUtils::Dot(reflect_vec, eye_vec);

			if (reflect_dot_eye > 0.0f)
			{
				float spec_factor = powf(reflect_dot_eye, material.Shininess());
				specular_cont = light_source.Intensity() * material.Specular() * spec_factor;
			}
		}
		
		return ambient_cont + diffuse_cont + specular_cont;
	}
}