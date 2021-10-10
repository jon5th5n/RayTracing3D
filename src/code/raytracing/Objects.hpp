#pragma once

class Ray;

//=======

class Object
{
public:
	Vector3 position;
	sf::Color color;

public:
	virtual std::tuple<bool, Vector3, Object*> getRayIntersection(Ray* ray) = 0;
};

//-------

class Sphere : public Object
{
public:
	Sphere(float x, float y, float z, float r, sf::Color c);

public:
	float radius;

public:
	std::tuple<bool, Vector3, Object*> getRayIntersection(Ray* ray) override;
};

//---

class Cuboid : public Object
{
public:
	Cuboid(float x, float y, float z, float w, float h, float d, sf::Color c);

public:
	float width;
	float height;
	float depth;

public:
	std::tuple<bool, Vector3, Object*> getRayIntersection(Ray* ray) override;
};