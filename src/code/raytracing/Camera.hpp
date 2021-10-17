#pragma once

#include "Objects.hpp"
#include "Ray.hpp"

//=======

class Camera
{
public:
	Camera(float x, float y, float z, unsigned int iw, unsigned int ih, float _scale, float _fov);

public:
	Vector3 position;
	float yaw;
	float pitch;

	unsigned int originalImageWidth;
	unsigned int originalImageHeight;
	float fov;

private:
	float scale;
	unsigned int imageWidth;
	unsigned int imageHeight;

	std::vector<std::vector<Ray>> rays;
	uint8_t* imageBuffer;

public:
	void calculateImageBuffer(Object* object, Light* light);
	void calculateImageBuffer(std::vector<Object*> objects, std::vector<Light*> lights);
	void clearImageBuffer();

	uint8_t* getImageBuffer();
	sf::Image getImage();

	float getScale();
	void setScale(float scale);
};