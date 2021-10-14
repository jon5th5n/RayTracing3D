#include "Objects.hpp"
#include "Ray.hpp"

//=======

Sphere::Sphere(float x, float y, float z, float r, sf::Color c)
{
	position = NewVector3(x, y, z);
	radius = r;
	color = c;
}

std::tuple<bool, Vector3, Object*> Sphere::getRayIntersection(Ray* ray)
{
	Vector3 c = position;
	float r = radius;

	Vector3 o = ray->origin;
	Vector3 u = ray->direction;

	float del = powf(Vector3DotProduct(u, Vector3Subtract(o, c)), 2) - (Vector3LengthSqr(Vector3Subtract(o, c)) - powf(r, 2));
	if (del < 0)
		return std::tuple<bool, Vector3, Object*> { false, Vector3Zero(), this };

	float d1 = -Vector3DotProduct(u, Vector3Subtract(o, c)) + sqrtf(del);
	float d2 = -Vector3DotProduct(u, Vector3Subtract(o, c)) - sqrtf(del);

	if (d1 < 0 && d2 < 0) // Object is behind the Ray
		return std::tuple<bool, Vector3, Object*> { false, Vector3Zero(), this };
	if (d1 == d2 || d1 < d2)
		return std::tuple<bool, Vector3, Object*> { true, Vector3Add(ray->origin, Vector3Scale(ray->direction, d1)), this };
	// if (d2 < d1) is the only remaining option
	return std::tuple<bool, Vector3, Object*> { true, Vector3Add(ray->origin, Vector3Scale(ray->direction, d2)), this };
}

//---

Cuboid::Cuboid(float x, float y, float z, float w, float h, float d, sf::Color c)
{
	position = NewVector3(x, y, z);
	width = w;
	height = h;
	depth = d;
	color = c;
}

std::tuple<bool, Vector3, Object*> Cuboid::getRayIntersection(Ray* ray)
{}