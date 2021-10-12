#include "Scene.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Objects.hpp"

//=======

void Scene::addCamera(Camera* camera)
{
	cameras.push_back(camera);
}

void Scene::addObject(Object* object)
{
	objects.push_back(object);
}

void Scene::addLight(Light* light)
{
	lights.push_back(light);
}

void Scene::calculateCameraImage(unsigned int nr)
{
	cameras[nr]->clearImageBuffer();
	cameras[nr]->calculateImageBuffer(objects);
}

void Scene::calculateCameraImages()
{
	for (Camera* camera : cameras)
	{
		camera->clearImageBuffer();
		camera->calculateImageBuffer(objects);
	}
}

sf::Image Scene::getCameraImage(unsigned int nr)
{
	return cameras[nr]->getImage();
}

uint8_t* Scene::getCameraImageBuffer(unsigned int nr)
{
	return cameras[nr]->getImageBuffer();
}

//---

void Scene::cameraMove(unsigned int nr, float xamount, float yamount, float zamount)
{
	cameras[nr]->position = Vector3Add(cameras[nr]->position, Vector3 { xamount, yamount, zamount });
}

void Scene::cameraMoveToDirection(unsigned int nr, float amount)
{}

void Scene::cameraMovePerpendicularToDirection(unsigned int nr, float amount)
{}

void Scene::cameraRotateYaw(unsigned int nr, float amount)
{
	cameras[nr]->yaw += amount;
	if (cameras[nr]->yaw > PI * 2)
		cameras[nr]->yaw -= PI * 2;
}

void Scene::cameraRotatePitch(unsigned int nr, float amount)
{
	cameras[nr]->pitch += amount;
	if (cameras[nr]->pitch > PI * 2)
		cameras[nr]->pitch -= PI * 2;
}