#include "Camera.hpp"
#include "Objects.hpp"
#include "Ray.hpp"

//=======

Camera::Camera(float x, float y, float z, unsigned int iw, unsigned int ih, float _fov)
{
	position = NewVector3(x, y, z);
	yaw = 0;
	pitch = 0;
	imageWidth = iw;
	imageHeight = ih;
	fov = _fov;

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

	imageBuffer = new uint8_t[imageWidth * imageHeight * 4];
}

void Camera::calculateImageBuffer(Object* object)
{
	for (unsigned int i = 0; i < imageWidth; i++)
	{
		for (unsigned int j = 0; j < imageHeight; j++)
		{
			Vector3 rayDir = Vector3RotateYaw(rays[i][j].direction, yaw);
			rayDir = Vector3RotatePitch(rayDir, pitch);
			Ray ray(position.x, position.y, position.z, rayDir);

			sf::Color c = ray.getColor(object);

			unsigned int index = (i + (j * imageWidth)) * 4;
			imageBuffer[index + 0] = c.r;
			imageBuffer[index + 1] = c.g;
			imageBuffer[index + 2] = c.b;
			imageBuffer[index + 3] = c.a;
		}
	}
}

void Camera::calculateImageBuffer(std::vector<Object*> objects)
{
	for (unsigned int i = 0; i < imageWidth; i++)
	{
		for (unsigned int j = 0; j < imageHeight; j++)
		{
			Vector3 rayDir = Vector3RotatePitch(rays[i][j].direction, pitch);
			rayDir = Vector3RotateYaw(rayDir, yaw);
			Ray ray(position.x, position.y, position.z, rayDir);

			sf::Color c = ray.getColor(objects);

			unsigned int index = (i + (j * imageWidth)) * 4;
			imageBuffer[index + 0] = c.r;
			imageBuffer[index + 1] = c.g;
			imageBuffer[index + 2] = c.b;
			imageBuffer[index + 3] = c.a;
		}
	}
}

void Camera::clearImageBuffer(sf::Color c)
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