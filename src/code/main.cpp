
// TODO: Add Lights and Camera movement through user input

#include "Platform/Platform.hpp"

#include "raytracing/Camera.hpp"
#include "raytracing/Light.hpp"
#include "raytracing/Objects.hpp"
#include "raytracing/Ray.hpp"
#include "raytracing/Scene.hpp"

int main()
{
	util::Platform platform;

	std::cout << "Hello World!" << std::endl;

	sf::RenderWindow window;
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());

	window.create(sf::VideoMode(900.0f * screenScalingFactor, 600.0f * screenScalingFactor), "SFML works!");
	platform.setIcon(window.getSystemHandle());

	sf::Event event;

	sf::Image image;
	image.create(900, 600, sf::Color::Magenta);
	sf::Texture renderTexture;
	renderTexture.loadFromImage(image);
	sf::Sprite renderSprite;
	renderSprite.setTexture(renderTexture);

	Scene scene;
	scene.addObject(new Sphere(50, -15, -10, 30, sf::Color::Red));
	scene.addObject(new Sphere(100, 15, 20, 15, sf::Color::Green));
	scene.addCamera(new Camera(0, 0, 0, 900, 600, 1.5));

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//-- process
		scene.calculateCameraImage(0);
		renderTexture.loadFromImage(scene.getCameraImage(0));

		//-- draw
		window.clear();

		window.draw(renderSprite);

		window.display();
	}

	return 0;
}
