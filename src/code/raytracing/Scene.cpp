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