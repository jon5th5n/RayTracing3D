#include "Ray.hpp"
#include "Objects.hpp"

//=======

// Ray::Ray()
// {
// 	origin = Vector3Zero();
// 	direction = Vector2Zero();
// }

Ray::Ray(float x, float y, float z, Vector3 dir)
{
	origin = NewVector3(x, y, z);
	direction = Vector3Normalize(dir);
}

std::pair<bool, Vector3> Ray::getIntersection(Object* object)
{
	auto [isIntersecting, intersection, objectPtr] = object->getRayIntersection(this);
	return std::pair<bool, Vector3> { isIntersecting, intersection };
}

std::pair<bool, Vector3> Ray::getIntersection(std::vector<Object*> objects)
{
	auto [isIntersecting, intersection, objectPtr] = getNearestIntersection(objects);
	return std::pair<bool, Vector3> { isIntersecting, intersection };
}

std::tuple<bool, Vector3, Object*> Ray::getNearestIntersection(std::vector<Object*> objects)
{
	Vector3 nearestIntersection;
	float nearestIntersectionDistance = std::numeric_limits<float>::infinity();
	Object* nearestObject;

	for (Object* object : objects)
	{
		auto [isIntersecting, intersection, objectPtr] = object->getRayIntersection(this);

		float intersectionDistance = Vector3Length(Vector3Subtract(intersection, origin));
		if (isIntersecting && intersectionDistance < nearestIntersectionDistance)
		{
			nearestIntersection = intersection;
			nearestIntersectionDistance = intersectionDistance;
			nearestObject = objectPtr;
		}
	}

	return std::tuple<bool, Vector3, Object*> { (nearestIntersectionDistance != std::numeric_limits<float>::infinity()), nearestIntersection, nearestObject };
}

sf::Color Ray::getColor(Object* object)
{
	auto [isIntersecting, intersection, objectPtr] = object->getRayIntersection(this);

	if (isIntersecting)
		return objectPtr->color;
	return sf::Color::Black;
}

sf::Color Ray::getColor(std::vector<Object*> objects)
{
	auto [isIntersecting, intersection, objectPtr] = getNearestIntersection(objects);

	if (isIntersecting)
		return objectPtr->color;
	return sf::Color::Black;
}