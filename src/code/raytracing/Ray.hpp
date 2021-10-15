#pragma once

class Object;
class Light;

//=======

class Ray
{
public:
	Ray() = default;
	Ray(float x, float y, float z, Vector3 dir);

public:
	Vector3 origin;
	Vector3 direction;

public:
	std::pair<bool, Vector3> getIntersection(Object* object);
	std::pair<bool, Vector3> getIntersection(std::vector<Object*> objects);
	std::tuple<bool, Vector3, Object*> getNearestIntersection(std::vector<Object*> objects);
	virtual sf::Color getColor(Object* object, Light* light);
	virtual sf::Color getColor(std::vector<Object*> objects, std::vector<Light*> lights);
};

//-------

// class PrimaryRay : public Ray
// {
// public:
// 	PrimaryRay(float x, float y, float z, Vector3 dir);

// public:
// 	Vector3 origin;
// 	Vector3 direction;

// public:
// 	sf::Color getColor() override;
// };