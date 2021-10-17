#include "Platform/Platform.hpp"

#include "raytracing/Camera.hpp"
#include "raytracing/Light.hpp"
#include "raytracing/Objects.hpp"
#include "raytracing/Ray.hpp"
#include "raytracing/Scene.hpp"

float random(float min, float max);
void handleInput(Scene* scene);

int main()
{
	util::Platform platform;

	std::cout << "Hello World!" << std::endl;

	sf::RenderWindow window;
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());

	window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width * screenScalingFactor, sf::VideoMode::getDesktopMode().height * screenScalingFactor), "ray tracer");
	platform.setIcon(window.getSystemHandle());

	window.setFramerateLimit(60);

	sf::Event event;

	sf::Font mainFont;
	mainFont.loadFromFile("content/Roboto-Regular.ttf");

	float fps = 0;
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	sf::Text fpsCounter(std::to_string((int)fps), mainFont, 20);
	fpsCounter.setPosition(2, 0);

	sf::Text scaleDisplay("", mainFont, 15);
	scaleDisplay.setPosition(2, 25);
	sf::Text positionDisplay("", mainFont, 10);
	positionDisplay.setPosition(2, 40);

	sf::Image image;
	image.create(window.getSize().x, window.getSize().y, sf::Color::Magenta);
	sf::Texture renderTexture;
	renderTexture.loadFromImage(image);
	sf::Sprite renderSprite;
	renderSprite.setTexture(renderTexture);

	Scene scene;
	for (int i = 0; i < 20; i++)
		scene.addObject(new Sphere(random(-200, 200), random(-200, 200), random(-50, 50), random(5, 50), sf::Color(random(0, 255), random(0, 255), random(0, 255))));
	for (int i = 0; i < 2; i++)
		scene.addLight(new Light(random(-350, 350), random(-350, 350), random(-350, 350), 1));
	scene.addCamera(new Camera(0, 0, 0, window.getSize().x, window.getSize().y, 0.2, 1.5));

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//-- process
		handleInput(&scene);

		scene.calculateCameraImage(0);
		renderTexture.loadFromImage(scene.getCameraImage(0));
		renderSprite.setScale(pow(scene.cameraGetScale(0), -1), pow(scene.cameraGetScale(0), -1));

		//-- draw
		window.clear();

		window.draw(renderSprite);

		window.draw(fpsCounter);
		window.draw(scaleDisplay);
		window.draw(positionDisplay);

		window.display();
		//-----

		currentTime = clock.getElapsedTime();
		fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
		previousTime = currentTime;
		fpsCounter.setString(std::to_string((int)fps));

		scaleDisplay.setString(std::to_string((int)(scene.cameraGetScale(0) * 100)) + "%");
		auto [cpx, cpy, cpz, cry, crp] = scene.cameraGetPositionAndRotation(0);
		positionDisplay.setString(std::to_string((int)cpx) + ", " + std::to_string((int)cpy) + ", " + std::to_string((int)cpz) + "\n" + std::to_string((int)(cry * RAD2DEG)) + ", " + std::to_string((int)(crp * RAD2DEG)));
	}

	return 0;
}

//=====

float random(float min, float max)
{
	return (min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min))));
}

//---

void handleInput(Scene* scene)
{
	float movementSpeed = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
		movementSpeed = 2;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		scene->cameraMoveToDirection(0, movementSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		scene->cameraMoveToDirection(0, -movementSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		scene->cameraMovePerpendicularToDirection(0, -movementSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		scene->cameraMovePerpendicularToDirection(0, movementSpeed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		scene->cameraMove(0, 0, 0, -movementSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		scene->cameraMove(0, 0, 0, movementSpeed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		scene->cameraRotateYaw(0, -1.5 * DEG2RAD * movementSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		scene->cameraRotateYaw(0, 1.5 * DEG2RAD * movementSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		scene->cameraRotatePitch(0, -1 * DEG2RAD * movementSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		scene->cameraRotatePitch(0, 1 * DEG2RAD * movementSpeed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		float currentScale = scene->cameraGetScale(0);
		scene->cameraSetScale(0, currentScale += 0.01);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		float currentScale = scene->cameraGetScale(0);
		scene->cameraSetScale(0, currentScale -= 0.01);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
	{
		scene->cameraSetScale(0, 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
	{
		scene->cameraSetScale(0, 0.2);
	}
}