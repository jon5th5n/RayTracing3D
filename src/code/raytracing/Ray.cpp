#include "Ray.hpp"
#include "Light.hpp"
#include "Objects.hpp"

//=======

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

sf::Color Ray::getColor(Object* object, Light* light)
{
	auto [isIntersecting, intersection, objectPtr] = object->getRayIntersection(this);

	if (isIntersecting)
		return objectPtr->color;
	return sf::Color::Black;
}

sf::Color Ray::getColor(std::vector<Object*> objects, std::vector<Light*> lights)
{
	auto [isIntersecting, intersection, objectPtr] = getNearestIntersection(objects);
	if (!isIntersecting)
		return sf::Color::Black;

	sf::Color color = objectPtr->color;

	Vector3 intersectionNormalVec = Vector3Normalize(Vector3Negate(Vector3Subtract(objectPtr->position, intersection)));

	std::vector<Light*> unintersectedLights;
	for (Light* light : lights)
	{
		Vector3 intersectionToLightDirVec = Vector3Normalize(Vector3Subtract(light->position, intersection));
		Ray intersectionToLightRay(intersection.x + intersectionNormalVec.x * 0.1, intersection.y + intersectionNormalVec.y * 0.1, intersection.z + intersectionNormalVec.z * 0.1, intersectionToLightDirVec);
		if (!std::get<0>(intersectionToLightRay.getNearestIntersection(objects)))
			unintersectedLights.push_back(light);
	}
	if (unintersectedLights.size() == 0)
		return sf::Color::Black;

	float brightness = 0;
	for (Light* light : unintersectedLights)
	{
		Vector3 intersectionToLightDirVec = Vector3Normalize(Vector3Subtract(light->position, intersection));
		float angleBetweenNormalAndLight = abs(Vector3AngleBetween(intersectionNormalVec, intersectionToLightDirVec));
		brightness += Clamp(Remap(angleBetweenNormalAndLight, 0, PI / 2, 1, 0), 0, 1) * light->brightness;
	}

	color = ColorMultiply(color, brightness);

	return color;
}