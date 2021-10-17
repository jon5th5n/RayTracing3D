#include "Camera.hpp"
#include "Objects.hpp"
#include "Ray.hpp"

//=======

Camera::Camera(float x, float y, float z, unsigned int iw, unsigned int ih, float _scale, float _fov)
{
	position = NewVector3(x, y, z);
	yaw = 0;
	pitch = 0;
	originalImageWidth = iw;
	originalImageHeight = ih;
	fov = _fov;

	imageBuffer = new uint8_t[1];
	setScale(_scale);
}

void Camera::calculateImageBuffer(Object* object, Light* light)
{
	for (unsigned int i = 0; i < imageWidth; i++)
	{
		for (unsigned int j = 0; j < imageHeight; j++)
		{
			Vector3 rayDir = Vector3RotateYaw(rays[i][j].direction, yaw);
			rayDir = Vector3RotatePitch(rayDir, pitch);
			Ray ray(position.x, position.y, position.z, rayDir);

			sf::Color c = ray.getColor(object, light);

			unsigned int index = (i + (j * imageWidth)) * 4;
			imageBuffer[index + 0] = c.r;
			imageBuffer[index + 1] = c.g;
			imageBuffer[index + 2] = c.b;
			imageBuffer[index + 3] = c.a;
		}
	}
}

void Camera::calculateImageBuffer(std::vector<Object*> objects, std::vector<Light*> lights)
{
	for (unsigned int i = 0; i < imageWidth; i++)
	{
		for (unsigned int j = 0; j < imageHeight; j++)
		{
			Vector3 rayDir = Vector3RotatePitch(rays[i][j].direction, pitch);
			rayDir = Vector3RotateYaw(rayDir, yaw);
			Ray ray(position.x, position.y, position.z, rayDir);

			sf::Color c = ray.getColor(objects, lights);

			unsigned int index = (i + (j * imageWidth)) * 4;
			imageBuffer[index + 0] = c.r;
			imageBuffer[index + 1] = c.g;
			imageBuffer[index + 2] = c.b;
			imageBuffer[index + 3] = c.a;
		}
	}
}

void Camera::clearImageBuffer()
{
	for (unsigned int i = 0; i < imageWidth * imageHeight * 4; i++)
		imageBuffer[i] = 255;
}

uint8_t* Camera::getImageBuffer()
{
	return imageBuffer;
}

sf::Image Camera::getImage()
{
	sf::Image img;
	img.create(imageWidth, imageHeight, imageBuffer);
	return img;
}

float Camera::getScale()
{
	return scale;
}

void Camera::setScale(float _scale)
{
	if (_scale < 0.01)
		scale = 0.01;
	else if (_scale > 1)
		scale = 1;
	else
		scale = _scale;

	imageWidth = (uint)(originalImageWidth * scale);
	imageHeight = (uint)(originalImageHeight * scale);

	rays.clear();
	for (unsigned int i = 0; i < imageWidth; i++)
	{
		std::vector<Ray> a;
		rays.push_back(a);
		for (unsigned int j = 0; j < imageHeight; j++)
		{
			float ir = Remap(i, 0, imageWidth, -0.5, 0.5);
			float jr = Remap(j, 0, imageHeight, (-0.5 / imageWidth) * imageHeight, (0.5 / imageWidth) * imageHeight);

			Ray ray = Ray(position.x, position.y, position.z, NewVector3(1 / fov, ir, jr));
			rays[i].push_back(ray);
		}
	}

	delete[] imageBuffer;
	imageBuffer = new uint8_t[imageWidth * imageHeight * 4];
}