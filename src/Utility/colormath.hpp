#pragma once
// added functionality for sfml colors

inline sf::Color NewColorSafe(int r, int g, int b, int a = 255)
{
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;

	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;

	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;

	if (a < 0)
		a = 0;
	else if (a > 255)
		a = 255;

	return sf::Color(r, g, b, a);
}

inline sf::Color NewColorSafe(float r, float g, float b, float a = 255)
{
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;

	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;

	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;

	if (a < 0)
		a = 0;
	else if (a > 255)
		a = 255;

	return sf::Color(r, g, b, a);
}

inline sf::Color ColorMultiply(sf::Color c, float v)
{
	return NewColorSafe((int)c.r * v, (int)c.g * v, (int)c.b * v);
}