#pragma once

class Camera;
class Object;
class Light;

//=======

class Scene
{
private:
	std::vector<Camera*> cameras;
	std::vector<Object*> objects;
	std::vector<Light*> lights;

public:
	void addCamera(Camera* camera);
	void addObject(Object* object);
	void addLight(Light* light);

	void calculateCameraImage(unsigned int nr);
	void calculateCameraImages();

	sf::Image getCameraImage(unsigned int nr);
	uint8_t* getCameraImageBuffer(unsigned int nr);
};