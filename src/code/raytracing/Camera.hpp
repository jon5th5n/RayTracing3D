#pragma once

#include "Objects.hpp"
#include "Ray.hpp"

//=======

//! xy rotation for yaw and xz rotation for pitch

class Camera
{
public:
	Camera(float x, float y, float z, unsigned int iw, unsigned int ih, float _fov);

public:
	Vector3 position;
	float yaw;
	float pitch;

	unsigned int imageWidth;
	unsigned int imageHeight;

	float fov;

private:
	std::vector<std::vector<Ray>> rays;
	uint8_t* imageBuffer;

public:
	void calculateImageBuffer(Object* object);
	void calculateImageBuffer(std::vector<Object*> objects);
	void clearImageBuffer(sf::Color c = sf::Color::White);

	uint8_t* getImageBuffer();
	sf::Image getImage();
};